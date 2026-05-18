# Session 19：Page fault、Hang 与 Reset

## 目标

进入故障恢复主题，理解 GPU page fault、hang、timeout、reset 和恢复路径。这个 session 建议尽量使用真实硬件补运行时证据。

## 核心问题

- Hang 是怎么被检测出来的？
- 驱动如何执行 reset 和恢复？
- page fault、scheduler timeout 和 GPU reset 之间是什么关系？

## 学习内容

### 1. 为什么故障恢复要放在提交路径之后学

page fault、hang、reset 不是孤立主题。它们都是正常提交路径失败后的分支。

正常路径是：

```text
submit -> scheduler -> ring -> GPU 执行 -> IRQ/fence signal
```

故障路径可能是：

```text
submit -> scheduler -> ring -> GPU 执行异常
    -> page fault / timeout / hang
    -> 收集错误状态
    -> 标记 guilty job 或上下文
    -> reset engine 或 GPU
    -> signal fence with error
    -> 恢复队列或让后续提交失败
```

所以本节要带着 Session 18 的 `job`、`ring`、`scheduler`、`fence` 视角来看，而不是只看日志里的错误字符串。

### 2. GPU page fault 和 CPU page fault 有什么不同

CPU page fault 通常发生在 CPU 执行某条访问内存的指令时，CPU 进入内核，由内核处理缺页、权限错误或崩溃。

GPU page fault 发生在 GPU 执行命令或 shader 时访问了某个 GPU 虚拟地址，但 GPU MMU/VM 找不到合法映射或权限不对。

常见原因包括：

- 用户态提交了错误 GPU VA。
- BO 没有正确 bind 到 VM。
- 页表更新还没完成就开始执行。
- 访问越界。
- 权限不匹配，例如写只读映射。
- reset 或 eviction 后状态不一致。

日志里常见信息可能包括：

```text
VM fault address
VMID / PASID / context id
fault status / access type
ring or engine
process name / pid
```

这些字段的价值是帮助你把 fault 反推到“哪个地址空间、哪个提交、哪个对象、哪类访问”。

### 3. Hang detection：谁发现 GPU 卡住了

GPU job 提交后，scheduler 或驱动通常会给它一个超时时间。如果 fence 长时间没有 signal，就可能触发 timeout。

简化模型：

```c
static enum drm_gpu_sched_stat my_timedout_job(struct drm_sched_job *s_job)
{
    struct my_job *job = to_my_job(s_job);

    my_gpu_dump_state(job->ring);
    my_gpu_reset(job->gpu);

    return DRM_GPU_SCHED_STAT_NOMINAL;
}
```

真实驱动里 timeout 处理非常复杂，但主线是：

1. scheduler 发现 job 超时。
2. 调用驱动的 `timedout_job` 回调。
3. 驱动收集 ring、register、VM、fence 状态。
4. 驱动决定 reset engine、reset ring，还是 reset 整个 GPU。
5. 相关 fence 以错误状态完成。
6. scheduler 尝试恢复后续 job 或停止队列。

### 4. guilty job 和无辜 job

当 GPU hang 住时，驱动要判断哪个 job 或上下文最可能导致故障。这个 job 常被称为 guilty job。

但实际情况可能很复杂：

- 真正错误的 job 可能已经执行过，后面的 job 才超时。
- 一个 engine 的 hang 可能影响其他 engine。
- page fault 可能来自某个进程，但 reset 影响全局。
- 硬件或固件问题可能让定位不稳定。

因此读日志时不要只看最后一条 timeout。要构造时间线：

```text
T0: 用户态提交 job A
T1: VM fault address X
T2: ring gfx timeout
T3: scheduler marks job A guilty
T4: GPU reset begins
T5: fences signaled with error
T6: device recovered / failed
```

时间线比孤立错误码更重要。

### 5. Reset 有不同粒度

reset 不是只有“重启 GPU”一种。不同驱动和硬件可能支持不同粒度：

- reset 某个 engine/ring。
- reset 某个 queue 或 context。
- reset 整个 GPU。
- reset 后重新初始化 firmware、VRAM、VM、display 相关状态。

粒度越小，对系统影响越小，但要求硬件支持和驱动恢复能力更强。

reset 后要处理的问题包括：

- 未完成 job 的 fence 怎么 signal。
- BO 和 VM 状态是否仍然有效。
- scheduler 队列是否恢复。
- 用户态是否收到 device lost 或错误返回。
- display 是否受影响。

### 6. 日志分析方法

一次有效的故障分析至少包含：

```text
环境：内核版本、GPU、驱动、Mesa/firmware 版本
触发方式：运行了什么程序或测试
时间线：从第一条异常到 reset 完成
错误类型：page fault / timeout / ring hang / reset fail
地址信息：fault address、VMID/PASID、engine
对象信息：可能涉及的 BO、VM、context、job
恢复结果：成功恢复、应用崩溃、设备不可用、系统挂起
源码入口：timeout/reset/fault handler
结论：已确认事实、推测、下一步验证
```

如果只能做源码阅读，也可以用公开日志或自己构造的示例日志练习这套模板。

### 7. 本节实践：从 timeout 回调往外画

定位入口：

```bash
rg -n "timedout_job|timeout|reset|gpu_reset|page fault|vm_fault|dma_fence_set_error" drivers/gpu/drm
```

记录模板：

```text
目标驱动：
scheduler timeout 回调：
page fault handler：
reset 入口：
错误状态 dump 函数：
fence 置错位置：
scheduler restart/stop 位置：
用户态可见错误：
需要真机验证的证据：
```

这节的目标不是制造故障，而是学会把故障恢复看成正常提交路径的异常分支。

## 建议源码入口

- `drivers/gpu/drm/scheduler/sched_main.c`
- `drivers/gpu/drm/amd/amdgpu/amdgpu_device.c`
- `drivers/gpu/drm/amd/amdgpu/amdgpu_job.c`
- `drivers/gpu/drm/amd/amdgpu/amdgpu_vm.c`
- 目标驱动中的 `timeout`、`reset`、`fault` 相关函数。

## 建议输出

- 故障恢复笔记
- hang dump 分析记录

## 完成标准

- 能解释 hang detection 到 reset 的大致控制流。
- 能指出目标驱动里 timeout/reset/page fault 的关键入口。
- 能写出一份日志分析记录，哪怕当前只能使用公开日志或历史日志样本。

## 关联 Lab

- [Lab 19：Page fault、Hang 与 Reset](../../labs/lab-19-page-fault-hang-reset/lab-19-page-fault-hang-reset.md)

## 下一步

进入 Session 20，把专题从渲染/计算故障转向显示输出和 page flip。

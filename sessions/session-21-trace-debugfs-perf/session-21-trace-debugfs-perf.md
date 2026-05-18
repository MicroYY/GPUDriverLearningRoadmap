# Session 21：Trace、debugfs、perf

## 目标

掌握调试 GPU 驱动时常用的运行时工具和日志入口，并学会把工具输出和源码路径对应起来。

## 核心问题

- 哪些 tracepoint、debugfs、perf 入口最值得先看？
- 如何把运行时现象和源码路径对应起来？
- 一次有效调试记录应该包含哪些证据？

## 学习内容

### 1. 调试工具各自看什么

GPU 驱动调试最容易犯的错误是“只看 dmesg”。dmesg 很重要，但它只是证据的一种。

可以先这样分工：

- `dmesg`
  看内核日志、WARN、错误码、reset、fault、驱动打印。

- DRM debug log
  打开更详细的 DRM/KMS/GEM/atomic 等调试输出。

- tracepoint / ftrace
  看事件时间线，例如 scheduler、fence、KMS commit、vblank。

- `debugfs`
  看驱动暴露的运行时状态，例如显存占用、ring、VM、gem object、display 状态。

- `perf`
  看 CPU 侧热点、锁等待、函数调用成本，不能直接告诉你 GPU 内部执行耗时，但能定位驱动 CPU 路径。

- IGT
  用标准测试构造可复现的 KMS/DRM 行为。

有效调试通常要组合多种证据，而不是只凭一条日志推断。

### 2. DRM debug log

很多内核支持通过模块参数打开 DRM debug：

```bash
cat /sys/module/drm/parameters/debug
sudo sh -c 'echo 0x1ff > /sys/module/drm/parameters/debug'
dmesg -w
```

不同内核版本的 bit 定义可能不同，使用时以当前内核文档和源码为准。你可以在源码里搜索 debug 分类：

```bash
rg -n "DRM_UT_|drm_dbg|drm_debug" drivers/gpu/drm include/drm
```

读日志时要记录：

- 打印来自哪个函数。
- 对应对象 id 是什么。
- 错误码是什么。
- 日志前后是否有 atomic、fence、reset、vblank 相关事件。

### 3. debugfs：看驱动当前状态

`debugfs` 通常挂载在 `/sys/kernel/debug`。DRM 相关节点常在：

```bash
sudo mount -t debugfs none /sys/kernel/debug
ls /sys/kernel/debug/dri/
find /sys/kernel/debug/dri -maxdepth 2 -type f | sort
```

不同驱动暴露节点不同。常见信息包括：

- GEM/BO 状态。
- VRAM/GTT 使用情况。
- ring 或 engine 状态。
- fence/seqno。
- KMS state。
- connector、plane、crtc 状态。

读取 debugfs 时要谨慎：部分节点可能很大，部分节点读取会触发锁或访问硬件状态。学习阶段先读小而明确的节点。

### 4. ftrace 和 trace-cmd

ftrace 可以记录内核 tracepoint 和函数调用。一个简单流程：

```bash
sudo trace-cmd list | grep -E "drm|dma_fence|gpu|sched"
sudo trace-cmd record -e drm -e dma_fence -- sleep 5
sudo trace-cmd report
```

如果没有 `trace-cmd`，也可以使用 tracefs：

```bash
cd /sys/kernel/tracing
sudo sh -c 'echo 0 > tracing_on'
sudo sh -c 'echo > trace'
sudo sh -c 'echo 1 > events/drm/enable'
sudo sh -c 'echo 1 > tracing_on'
sleep 5
sudo cat trace
```

具体事件是否存在取决于内核配置。不要把某个事件名当成所有环境都有，先 `ls events/` 或 `trace-cmd list`。

### 5. perf 看 CPU 侧路径

`perf` 适合回答“CPU 时间花在哪里”，例如驱动是否卡在锁、内存分配、ioctl 路径或等待。

示例：

```bash
sudo perf top -g
sudo perf record -g -- ./your_test
sudo perf report
```

如果你看到大量时间在 `dma_fence_wait`、`schedule`、`mutex_lock`，说明 CPU 侧可能在等待某个异步事件或锁。它不直接证明 GPU 慢，但能帮助你定位“用户态为什么卡住”。

### 6. 一次调试记录应该长什么样

建议固定格式：

```text
目标问题：
环境：内核、GPU、Mesa、驱动、测试命令
复现步骤：
预期结果：
实际结果：
dmesg 关键片段：
trace 关键事件：
debugfs 关键状态：
perf 观察：
对应源码入口：
已确认事实：
仍然只是推测的部分：
下一步验证：
```

这个格式能强迫你区分事实和推测。GPU 驱动问题经常跨用户态、内核态和硬件，没有证据链很容易误判。

### 7. 本节实践：建立自己的工具速查表

写一张表：

```text
工具：dmesg
适合看：
常用命令：
源码对应：
局限：

工具：debugfs
适合看：
常用命令：
源码对应：
局限：

工具：trace
适合看：
常用命令：
源码对应：
局限：
```

以后每做一个 lab，都把工具输出和源码函数对应起来。这样调试能力会比单纯背命令扎实很多。

## 建议源码入口

- `drivers/gpu/drm/drm_debugfs.c`
- `drivers/gpu/drm/drm_trace.h`
- `drivers/gpu/drm/scheduler/`
- 目标驱动中的 `debugfs`、`trace`、`seq_file` 相关实现。
- `/sys/kernel/debug/dri/` 对应运行时节点。

## 建议输出

- 一次调试记录
- 工具速查表

## 完成标准

- 能列出至少 5 个 GPU/DRM 调试入口及适用场景。
- 能把一次工具输出对应到至少一个源码函数或结构体。
- 能说明哪些调试能力在 QEMU 中可用，哪些依赖真实 GPU。

## 关联 Lab

- [Lab 21：Trace、debugfs、perf](../../labs/lab-21-trace-debugfs-perf/lab-21-trace-debugfs-perf.md)

## 下一步

进入 Session 22，把前面所有知识收束到一次完整 ioctl 路径解剖。

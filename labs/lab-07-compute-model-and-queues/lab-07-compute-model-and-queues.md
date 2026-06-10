# Lab 07：GPU 计算模型与队列

## 对应 Session

- [Session 07：GPU 计算模型与队列](../../sessions/session-07-compute-model-and-queues/session-07-compute-model-and-queues.md)

## 目标

理解 wave/warp、queue、doorbell 和 command buffer 的关系。

## 开始前先确认

- 已经完成 Session 07。
- 如果没有目标硬件，可以只做源码和概念图，不影响本 lab 主目标。

## 任务

### 1. 比较三类 queue

用表格比较：

- graphics queue
- compute queue
- copy / DMA queue

至少比较职责、典型命令、同步需求和常见硬件资源。

### 2. 画出 queue 与 command buffer 的关系图

图里至少包含：

- 用户态构建 command buffer
- ioctl 或用户态队列提交
- kernel scheduler 或硬件队列
- ring buffer
- doorbell
- fence

### 3. 解释 doorbell 的含义

用自己的话回答：

- doorbell 通常写到哪里。
- 为什么写 doorbell 可以通知 GPU。
- 它和“把命令写进 ring”是什么关系。

### 4. 完成 queue `ops table` 代码实验

本 lab 提供一个最小 C 代码框架，用固定容量 pending 队列模拟“同一个 queue 对象绑定不同 ops 后表现出不同提交策略”。

代码目录：

- [code](code/README.md)

需要补充实现的文件：

- [queue_ops.h](code/include/queue_ops.h)
- [queue_ops.c](code/src/queue_ops.c)

测试入口：

- [test_queue_ops.c](code/tests/test_queue_ops.c)

在 Windows PowerShell 里运行：

```powershell
cd labs\lab-07-compute-model-and-queues\code
powershell -ExecutionPolicy Bypass -File .\run-tests.ps1
```

在 Linux / WSL 里运行：

```bash
cd labs/lab-07-compute-model-and-queues/code
make test
```

初始代码里保留了 `TODO(student)`，所以第一次运行测试失败是正常的。建议按下面顺序补：

1. 实现 `gpu_queue_init`
2. 实现 `pending_count`
3. 实现 FIFO 的 `submit_tail`
4. 实现 LIFO 的 `submit_head`
5. 实现 `complete_next`

通过测试后，你应该能解释：

- `struct gpu_queue_ops` 为什么像一个小型接口表。
- 同一个 `struct gpu_queue` 为什么能通过不同 `ops` 实现 FIFO / LIFO。
- scheduler backend ops、KMS helper funcs 这类真实驱动回调表和这个模型有什么相似点。

### 5. 找一条真实 submit 入口

任选一个驱动，定位 submit、scheduler、ring 或 doorbell 相关代码：

```bash
rg -n "submit|drm_sched|ring|doorbell|wptr|run_job" drivers/gpu/drm/amd drivers/gpu/drm/msm drivers/gpu/drm/panfrost drivers/gpu/drm/xe
```

不要求读完，只要记录一个你认为最接近“提交进入驱动”的入口，以及一个你认为最接近“通知硬件”的入口。

## 交付物

- 计算模型笔记
- queue 关系图
- 通过测试的 queue `ops table` 示例
- submit 入口定位记录

## 检查项

- [ ] 我能解释 wave/warp/workgroup 的基本含义。
- [ ] 我能区分 queue、ring、command buffer。
- [ ] 我能解释 doorbell 在提交路径中的位置。
- [ ] 我完成了 `code/` 目录里的 queue `ops table` 实验。
- [ ] 我能指出至少一个真实驱动里的 submit 或 ring 相关入口。

## 完成标准

- 你能把一次 GPU 计算或图形提交拆成“组织命令、排队、通知硬件、等待完成”。

# Lab 19：Page fault、Hang 与 Reset

## 对应 Session

- [Session 19：Page fault、Hang 与 Reset](../../sessions/session-19-page-fault-hang-reset/README.md)

## 目标

学习 GPU hang、timeout 和 reset 的检测与恢复。

## 开始前先确认

- 已经完成 Session 19。
- 真机优先。没有真实 GPU 时，可以使用源码路径和公开日志样本完成分析框架。

## 任务

### 1. 抓取或收集一组 hang / reset 相关日志

日志可以来自：

- 自己的真实机器。
- 内核 bug report。
- CI 日志。
- 公开邮件列表或 issue 中的片段。

记录触发条件、时间线、错误码和恢复结果。

### 2. 找到驱动中的 timeout 或 reset 入口

至少定位：

- scheduler timeout。
- job timeout callback。
- device reset。
- ring reset。
- VM fault 或 page fault 处理。

建议命令：

```bash
rg -n "timedout_job|timeout|gpu_reset|reset|page fault|vm_fault|dma_fence_set_error" drivers/gpu/drm drivers/gpu/drm/scheduler
```

### 3. 总结恢复流程

写出：

- 检测到了什么。
- 哪个 job 或 context 被认为有问题。
- 驱动如何停止、reset、恢复或上报失败。
- fence 和用户态等待者最终看到什么结果。

### 4. 写一份故障时间线

```text
T0 触发条件：
T1 第一条异常日志：
T2 fault/timeout 入口：
T3 guilty job/context：
T4 reset 开始：
T5 fence/error 上报：
T6 恢复结果：
还无法确认的部分：
```

## 交付物

- 故障恢复笔记
- dump / 日志分析
- 故障时间线

## 检查项

- [ ] 我有一份日志或源码路径样本。
- [ ] 我找到 timeout/reset/fault 至少两个入口。
- [ ] 我能写出恢复流程时间线。
- [ ] 我区分了日志能证明的事实和自己的推测。

## 完成标准

- 你能把 hang/reset 从“玄学日志”拆成检测、定位、恢复、上报四个阶段。

# Lab 07：GPU 计算模型与队列

## 对应 Session

- [Session 07：GPU 计算模型与队列](../../sessions/session-07-compute-model-and-queues/README.md)

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

### 4. 找一条真实 submit 入口

任选一个驱动，定位 submit、scheduler、ring 或 doorbell 相关代码：

```bash
rg -n "submit|drm_sched|ring|doorbell|wptr|run_job" drivers/gpu/drm/amd drivers/gpu/drm/msm drivers/gpu/drm/panfrost drivers/gpu/drm/xe
```

不要求读完，只要记录一个你认为最接近“提交进入驱动”的入口，以及一个你认为最接近“通知硬件”的入口。

## 交付物

- 计算模型笔记
- queue 关系图
- submit 入口定位记录

## 检查项

- [ ] 我能解释 wave/warp/workgroup 的基本含义。
- [ ] 我能区分 queue、ring、command buffer。
- [ ] 我能解释 doorbell 在提交路径中的位置。
- [ ] 我能指出至少一个真实驱动里的 submit 或 ring 相关入口。

## 完成标准

- 你能把一次 GPU 计算或图形提交拆成“组织命令、排队、通知硬件、等待完成”。

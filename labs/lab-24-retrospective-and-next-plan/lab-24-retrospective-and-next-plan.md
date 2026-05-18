# Lab 24：总结与下一阶段计划

## 对应 Session

- [Session 24：总结与下一阶段计划](../../sessions/session-24-retrospective-and-next-plan/session-24-retrospective-and-next-plan.md)

## 目标

完成整套路线的复盘，并输出下一阶段行动计划。

## 开始前先确认

- 已经完成 Session 24。
- 已经尽量整理前面 lab 的笔记、图、日志和源码路径。

## 任务

### 1. 总结目前已经掌握的内容

至少按下面几类写：

- 图形栈分层。
- 内核对象阅读。
- DRM/KMS。
- 显存管理。
- 命令提交和同步。
- 调试工具。

每一类都至少写一个可复查证据，例如源码入口、路径图、日志、命令或 lab 输出。

### 2. 梳理还不清楚的问题

列出 5 到 10 个问题，并标注：

- 属于哪个主题。
- 需要源码阅读、实验环境还是真机验证。
- 下一步入口。

### 3. 写出下一阶段 8 周计划

每周写清：

- 主题。
- 源码入口。
- lab 或验证方式。
- 输出物。
- 风险或依赖。

### 4. 选三条路径做最终自测

从下面任选三条，用 Lab 22 的方式写完整路径：

- `DRM_IOCTL_VERSION`
- dumb buffer create / mmap / framebuffer
- atomic page flip 到 vblank event
- GEM/BO create 到 dma-buf export
- submit ioctl 到 fence signal
- job timeout 到 reset
- probe 到 `drm_dev_register`

## 交付物

- 阶段总结
- 下一阶段计划
- 三条最终自测路径

## 检查项

- [ ] 我整理了前面 24 个 session 的主要输出。
- [ ] 我列出仍不清楚的问题。
- [ ] 我写出下一阶段 8 周计划。
- [ ] 我完成了至少三条路径的最终自测。

## 完成标准

- 你能明确说出自己已经能独立阅读哪些路径，以及下一阶段要补哪条能力链。

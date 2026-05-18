# Lab 10：Atomic modeset 与 IGT 基础

## 对应 Session

- [Session 10：Atomic modeset 与 IGT 基础](../../sessions/session-10-atomic-modeset-and-igt/session-10-atomic-modeset-and-igt.md)

## 目标

理解 atomic commit，并用 IGT 验证基础 KMS 行为。

## 开始前先确认

- 已经完成 Session 10。
- 推荐在 QEMU + `vkms` 或原生 Linux 中执行。
- 如果当前环境跑不了 IGT，可以先阅读一个 `kms_*` 测试并记录它验证什么。

## 任务

### 1. 准备或阅读 IGT

优先选择：

- 编译 `igt-gpu-tools`。
- 或阅读一个 `tests/kms_*` 测试源文件。

建议先定位 atomic 相关测试：

```bash
rg -n "igt_display_commit_atomic|DRM_MODE_ATOMIC|kms_atomic|plane" igt-gpu-tools/tests/kms_*
```

### 2. 运行或静态分析一个 KMS 测试

推荐从简单测试开始，例如和 `vkms`、plane、atomic、basic modeset 相关的测试。

记录：

- 测试命令。
- pass / fail / skip 结果。
- 相关 `dmesg`。
- 测试覆盖的 KMS 对象或 property。
- 失败时的 errno 或 skip 原因。

### 3. 对照源码理解 atomic 流程

至少追到：

- atomic state 创建。
- check 阶段。
- commit 阶段。
- event 或 vblank 相关处理。

### 4. 写一份 IGT 结果解剖表

```text
测试文件：
subtest：
目标对象：
设置的 property：
期望结果：
实际结果：
dmesg 关键日志：
对应内核入口：
下一步判断：
```

## 交付物

- IGT 运行记录
- atomic modeset 观察笔记
- IGT 结果解剖表

## 检查项

- [ ] 我能解释 atomic check 和 commit 的职责差异。
- [ ] 我能说明一个 IGT 测试在验证什么。
- [ ] 我记录了命令、结果、日志和源码入口。
- [ ] 我能把一次 pass/fail/skip 和具体 KMS 对象或 property 联系起来。

## 完成标准

- 你能把一次 IGT 结果和 KMS/atomic 源码路径联系起来，而不是只记录 pass/fail。

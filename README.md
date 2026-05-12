# GPU Driver Learning Roadmap

一个面向自学者和工程师的 GPU 驱动课程型仓库，采用“roadmap + sessions + labs”的组织方式，帮助你系统学习 Linux GPU 驱动栈，并逐步过渡到真实驱动源码阅读、运行时观察和实验复盘。

## 这个仓库是做什么的

这个仓库不是单纯的一篇学习笔记，而是一套以 session 为核心的学习工作区。它把 24 周路线拆成可执行的学习单元，每个单元都有对应 lab，用来把概念、源码路径和实验记录连起来。

- `docs/` 保存序言、路线图、源码阅读清单和每周复盘模板。
- `sessions/` 把 roadmap 里的每个学习主题映射成一个课程单元。
- `labs/` 提供同号实验任务，帮助把“看懂”变成“能验证、能复盘”。

## 适合谁

- 有 C 语言和基础操作系统知识，想进入 GPU 驱动方向的人。
- 想系统学习 Linux DRM/KMS、显存管理、命令提交和同步机制的人。
- 做图形、编译器、系统软件或内核开发，想补 GPU 驱动知识的人。

## 学习完成后你应该能做到

- 说清 Linux 图形栈的主要分层和职责。
- 看懂 DRM/KMS 的常见对象和关键数据流。
- 读懂简单 GPU 驱动的初始化、buffer 管理和命令提交流程。
- 对 `i915/xe`、`amdgpu`、`msm`、`panfrost` 这类真实驱动有明确切入点。
- 熟练使用 IGT (igt-gpu-tools) 进行内核驱动测试，并能分析常见 GPU Hang 和 Reset 的错误日志。

## 仓库结构

```text
.
├─ .gitignore
├─ LICENSE
├─ CONTRIBUTING.md
├─ README.md
├─ docs/
│  ├─ preface.md
│  ├─ roadmap.md
│  ├─ reading_checklist.md
│  └─ weekly-template.md
├─ sessions/
│  ├─ README.md
│  ├─ session-01-environment-and-stack/
│  │  └─ README.md
│  ├─ session-02-c-and-kernel-structures/
│  │  └─ README.md
│  ├─ ...
│  └─ session-24-retrospective-and-next-plan/
│     └─ README.md
├─ labs/
│  ├─ README.md
│  ├─ lab-01-environment-and-stack/
│  │  └─ README.md
│  ├─ lab-02-c-and-kernel-structures/
│  │  └─ README.md
│  ├─ ...
│  └─ lab-24-retrospective-and-next-plan/
│     └─ README.md
```

## 从哪里开始

建议按下面顺序使用这个仓库：

1. 先读 [序言](docs/preface.md)，了解学习目标和方法。
2. 再读 [长期路线图](docs/roadmap.md)，建立 24 周整体地图。
3. 从 [Session 导航](sessions/README.md) 开始，按顺序推进。
4. 在对应时间窗口完成配套 lab。
5. 用 [每周复盘模板](docs/weekly-template.md) 记录自己的输出。

## Sessions

- [Session 导航](sessions/README.md)
- [Session 01：环境准备与图形栈总览](sessions/session-01-environment-and-stack/README.md)
- [Session 10：Atomic modeset 与 IGT 基础](sessions/session-10-atomic-modeset-and-igt/README.md)
- [Session 13：阅读 `vkms`](sessions/session-13-read-vkms/README.md)
- [Session 19：Page fault、Hang 与 Reset](sessions/session-19-page-fault-hang-reset/README.md)

## 实验导航

lab 现在按 session 一一对应组织，建议直接从总索引进入：

- [Lab 导航](labs/README.md)
- Session 01 对应 Lab 01
- Session 02 对应 Lab 02
- ...
- Session 24 对应 Lab 24

## 推荐学习方式

Lab 不等于“每周都必须写内核模块”。在这套课程里，只要能留下可复查的证据，下面几类都算有效 lab：

1. 代码实验：编写最小用户态程序、调用 `ioctl`、修改或加载 `vkms`。
2. 路径追踪：用源码、`ftrace`、`bpftrace` 或日志追一次真实调用链。
3. 对象解剖：阅读关键结构体，画出对象关系、生命周期或状态流转。
4. 调试记录：运行 IGT、观察 `debugfs`、分析 `dmesg` 或 perf/trace 输出。

建议每周按同一个节奏推进：先读 session，明确问题；再做同号 lab，留下证据；最后用复盘模板记录“我现在能解释什么、还卡在哪里”。

## 当前状态

当前仓库已经切换到 session 主导的结构，后续执行时可以使用以下辅助文档来驱动学习并检验产出进度：

- [源码阅读 Checklist](docs/reading_checklist.md)：进入陌生驱动目录时，用它快速找到入口、对象、提交、同步和调试线索。
- [每周复盘模板](docs/weekly-template.md)：每周把实验、路径追踪、问题清单和下一步计划写下来。

## 相关文档

- [docs/preface.md](docs/preface.md)
- [docs/roadmap.md](docs/roadmap.md)
- [docs/reading_checklist.md](docs/reading_checklist.md)
- [docs/weekly-template.md](docs/weekly-template.md)
- [sessions/README.md](sessions/README.md)
- [labs/README.md](labs/README.md)

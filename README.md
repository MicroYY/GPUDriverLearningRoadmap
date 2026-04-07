# GPU Driver Learning Roadmap

一个面向自学者和工程师的 GPU 驱动课程型仓库，采用“roadmap + sessions + labs”的组织方式，帮助你系统学习 Linux GPU 驱动栈，并逐步过渡到真实驱动源码阅读与实验。

## 这个仓库是做什么的

这个仓库不是单纯的一篇学习笔记，而是一套以 session 为核心的学习工作区：

- `docs/` 保存序言、路线图、阅读清单和模板。
- `sessions/` 把 roadmap 里的每个学习主题直接映射成一个 session。
- `labs/` 提供配套实验任务，帮助把概念变成可验证的理解。

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
│  ├─ session-01-environment-and-stack.md
│  ├─ session-02-c-and-kernel-structures.md
│  ├─ ...
│  └─ session-24-retrospective-and-next-plan.md
├─ labs/
│  ├─ README.md
│  ├─ lab-01-environment-and-stack/
│  ├─ lab-02-c-and-kernel-structures/
│  ├─ ...
│  └─ lab-24-retrospective-and-next-plan/
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
**💡 关于 Lab 的定义（打破“必须写代码才算实验”的误区）：**
在这个实战框架下，并非每一周都要去编译内核模块。我们将以下形式均视为闭环的 Lab 产出：
1. **代码实验 (Coding Lab)**：如编写简单的 char device、调用 `ioctl`、修改 `vkms` 等。
2. **追踪实验 (Trace Lab)**：使用 `ftrace`/`bpftrace` 验证从用户态到 `drm_ioctl` 的真实执行路径。
3. **图解实验 (Diagram Lab)**：不写代码，但通过通读关键源码文件，绘制出 DRM 核心对象的关系图或生命周期状态机。
4. **调试实验 (Debug Lab)**：编译并运行 IGT (igt-gpu-tools) 跑出 pass/fail 结果，或去 `/sys/kernel/debug/dri/` 下观察 GPU 状态节点。


- 每周安排固定时间读一个或多个 session。
- 每周至少完成一个小输出：笔记、图、源码路径追踪或实验记录。
- 不要把 lab 当作附属品，lab 才是把“知道”变成“会”的关键。

## 当前状态

当前仓库已经切换到 session 主导的结构，后续执行时可以使用以下辅助文档来驱动学习并检验产出进度：

- [📝 源码阅读核心 Checklist: `docs/reading_checklist.md`](docs/reading_checklist.md) - 在迷失在代码海前，看看这 8 个必须回答的硬核问题。
- [📆 本周学习与代码复盘笔记模板: `docs/weekly-template.md`](docs/weekly-template.md) - 每周把你的实验、路径追踪和问题清单写下来。

## 相关文档

- [docs/preface.md](docs/preface.md)
- [docs/roadmap.md](docs/roadmap.md)
- [docs/reading_checklist.md](docs/reading_checklist.md)
- [docs/weekly-template.md](docs/weekly-template.md)
- [sessions/README.md](sessions/README.md)
- [labs/README.md](labs/README.md)

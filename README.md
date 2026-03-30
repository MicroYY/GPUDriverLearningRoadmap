# GPU Driver Learning Roadmap

一个面向自学者和工程师的 GPU 驱动课程型仓库，采用“课程模块 + lab + 笔记 + 图示”的组织方式，帮助你系统学习 Linux GPU 驱动栈，并逐步过渡到真实驱动源码阅读与实验。

## 这个仓库是做什么的

这个仓库不是单纯的一篇学习笔记，而是一套可持续扩展的学习工作区：

- `modules/` 提供按主题组织的课程内容。
- `labs/` 提供配套实验任务，帮助把概念变成可验证的理解。
- `notes/` 用来记录每周学习笔记、源码解读和问题清单。
- `diagrams/` 用来沉淀对象关系图、流程图和数据路径图。
- `docs/` 保存序言、长期路线图和其他说明性文档。

## 适合谁

- 有 C 语言和基础操作系统知识，想进入 GPU 驱动方向的人。
- 想系统学习 Linux DRM/KMS、显存管理、命令提交和同步机制的人。
- 做图形、编译器、系统软件或内核开发，想补 GPU 驱动知识的人。

## 学习完成后你应该能做到

- 说清 Linux 图形栈的主要分层和职责。
- 看懂 DRM/KMS 的常见对象和关键数据流。
- 读懂简单 GPU 驱动的初始化、buffer 管理和命令提交流程。
- 对 `i915/xe`、`amdgpu`、`msm`、`panfrost` 这类真实驱动有明确切入点。

## 仓库结构

```text
.
├─ README.md
├─ docs/
│  ├─ preface.md
│  └─ roadmap.md
├─ modules/
│  ├─ README.md
│  ├─ module-01-foundations/
│  ├─ module-02-gpu-basics/
│  ├─ module-03-drm-kms/
│  ├─ module-04-driver-reading/
│  └─ module-05-advanced-topics/
├─ labs/
│  ├─ README.md
│  ├─ lab-01-environment/
│  ├─ lab-02-ioctl-tracing/
│  └─ lab-03-bo-lifecycle/
├─ notes/
│  └─ README.md
└─ diagrams/
   └─ README.md
```

## 从哪里开始

建议按下面顺序使用这个仓库：

1. 先读 [序言](docs/preface.md)，了解学习目标和方法。
2. 再读 [长期路线图](docs/roadmap.md)，建立 24 周整体地图。
3. 从 [课程模块导航](modules/README.md) 开始，按模块推进。
4. 每学完一个模块，配套完成对应 lab。
5. 把输出整理到 `notes/` 和 `diagrams/` 中。

## 课程模块

- [模块 1：基础准备](modules/module-01-foundations/README.md)
- [模块 2：GPU 与图形基础](modules/module-02-gpu-basics/README.md)
- [模块 3：Linux DRM/KMS 核心](modules/module-03-drm-kms/README.md)
- [模块 4：真实驱动源码阅读](modules/module-04-driver-reading/README.md)
- [模块 5：专题攻坚](modules/module-05-advanced-topics/README.md)

## 实验导航

- [Lab 1：环境准备与源码工作区](labs/lab-01-environment/README.md)
- [Lab 2：跟踪一次 `ioctl` 调用路径](labs/lab-02-ioctl-tracing/README.md)
- [Lab 3：阅读一个 buffer object 的生命周期](labs/lab-03-bo-lifecycle/README.md)

## 推荐学习方式

- 每周安排固定时间读模块内容。
- 每周至少完成一个小输出：笔记、图、源码路径追踪或实验记录。
- 不要把 lab 当作附属品，lab 才是把“知道”变成“会”的关键。

## 当前状态

当前仓库已经完成第一版骨架，后续可以继续补充：

- 每个模块的详细讲义
- 每个 lab 的验收标准和参考输出
- 每周笔记模板
- 图示模板和源码阅读 checklist

## 相关文档

- [docs/preface.md](docs/preface.md)
- [docs/roadmap.md](docs/roadmap.md)
- [modules/README.md](modules/README.md)
- [labs/README.md](labs/README.md)

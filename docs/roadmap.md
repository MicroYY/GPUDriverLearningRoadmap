# 24 周学习路线图

## 总目标

这份路线图以 Linux 开源 GPU 驱动栈为主线，帮助你在 24 周内建立下面这些能力：

1. 理解 GPU 驱动在整个图形栈里的位置。
2. 看懂 Linux DRM/KMS 的核心概念和常见对象。
3. 能阅读典型 GPU 驱动源码，例如 `vkms`、`msm`、`i915/xe`、`amdgpu`。
4. 理解显存管理、命令提交、同步、中断、显示输出这些关键机制。
5. 为后续深入图形驱动、计算驱动或内核开发打基础。

## 如何阅读这份路线图

这个仓库现在使用两个主维度：

- `roadmap` 是时间维度，回答“第几周学什么”。
- `sessions` 是执行维度，把每个学习主题直接落成一个 session 文件。

`labs` 继续保留，并且现在尽量做到“每个 session 对应一个单独 lab”，方便按周推进和复盘。

建议每周按下面的闭环推进：

1. 读 session，先理解本周概念、对象和源码入口。
2. 做同号 lab，把理解落成图、函数链、命令输出或日志分析。
3. 用 [weekly-template.md](./weekly-template.md) 复盘，把“已确认事实”和“仍然推测”分开。
4. 下周开始前，先回看上一周留下的问题。

这套路线不要求每周都跑出真实硬件实验。关键是每周都留下可复查的证据：源码路径、最小代码、运行命令、日志、trace、debugfs 输出或对象关系图。

## 建议环境

推荐直接准备下面两类环境之一：

- 原生 Linux 测试机
- QEMU Linux 虚拟机

这两类环境最适合完成这套课程里的源码阅读、KMS/DRM 实验、IGT、`debugfs`、`trace`、`perf` 和日志抓取。

如果你的宿主机是 Windows，也可以用 Windows 上的 QEMU 跑 Linux guest 来完成前半段和通用 DRM/KMS lab。需要注意的是，普通 QEMU 更适合承担通用 Linux 图形栈、`virtio-gpu`、`vkms` 相关实验，不等于自动拥有 `amdgpu`、`i915/xe`、`msm`、`panfrost` 这些真实目标驱动的完整实验条件。

后面的表格使用三个环境标签：

- `QEMU 可完成`：普通 QEMU Linux guest 足够完成主要 lab。
- `源码可完成`：即使没有对应硬件，也能通过源码阅读和路径分析完成主要目标。
- `真机优先`：建议使用真实 GPU 或真实显示环境，否则运行时证据会明显不足。

## QEMU 适配范围

| Session | QEMU 适配度 | 说明 |
| --- | --- | --- |
| Session 01-08 | 可完成 | 这一段以概念建立、源码阅读、最小示例和分层理解为主。 |
| Session 09-10 | 可完成 | 配合 `vkms` 可做 KMS 对象观察、atomic modeset 和 IGT 基础实验。 |
| Session 11-14 | 可完成 | 通用 DRM/GEM/KMS 路径阅读和 `vkms` / `simpledrm` 相关内容适合在 QEMU 中推进。 |
| Session 15-18 | 部分可完成 | 可以做源码阅读和路径分析，但普通 QEMU 不提供 `msm`、`panfrost`、`i915/xe`、`amdgpu` 这些目标驱动的真实实验环境。 |
| Session 19 | 不建议仅用 QEMU | hang、reset、page fault 这类故障恢复主题更适合真实硬件和真实驱动环境。 |
| Session 20 | 部分可完成 | 可以学习 page flip、KMS 和 vblank 的通用路径，但真实显示链路验证能力有限。 |
| Session 21 | 部分可完成 | 通用 `trace`、`debugfs`、`perf` 可以做，但真实 GPU 专有节点和问题场景不足。 |
| Session 22 | 可完成 | 静态路径分析和部分运行验证可以在 QEMU 中完成。 |
| Session 23-24 | 可完成 | 主要是总结、选题和制定下一阶段计划。 |

## WSL2 适配范围

- Session 01 到 Session 08 基本可以正常学习，因为这一段以概念建立、源码阅读、最小示例和分层理解为主。
- Session 09 会在 `modetest` 和真实 KMS 对象观察上受限。
- Session 10 会在 `vkms`、IGT 和 `dmesg` 观察上明显受限。
- Session 12 会在 vblank / IRQ / fence 的运行时验证上受限。
- Session 19 会在 hang / reset 日志抓取和故障恢复观察上受限。
- Session 20 会在 page flip、显示输出和 vblank 观察上受限。
- Session 21 会在 DRM 相关 `debugfs`、trace、`perf` 实验上受限。
- Session 22 如果你想做一次带运行验证的完整 `ioctl` 路径跟踪，也会受限。

结论很简单：

- 只想先学路线、读源码、记笔记，WSL2 可以用。
- 想把这套课程后半段的大多数 lab 认真做完，建议一开始就用原生 Linux 或 QEMU。

## Session 映射总览

| 周数 | Session | 学习主题 | 关联 Lab | 环境 | 输出 |
| --- | --- | --- | --- | --- | --- |
| 1 | [Session 01](../sessions/session-01-environment-and-stack/session-01-environment-and-stack.md) | 环境准备、图形栈总览 | [Lab 01](../labs/lab-01-environment-and-stack/lab-01-environment-and-stack.md) | QEMU 可完成 | 环境记录和总览图 |
| 2 | [Session 02](../sessions/session-02-c-and-kernel-structures/session-02-c-and-kernel-structures.md) | C 和内核常见数据结构 | [Lab 02](../labs/lab-02-c-and-kernel-structures/lab-02-c-and-kernel-structures.md) | 源码可完成 | 结构体、链表、锁笔记 |
| 3 | [Session 03](../sessions/session-03-virtual-memory-dma-iommu/session-03-virtual-memory-dma-iommu.md) | 虚拟内存、DMA、IOMMU | [Lab 03](../labs/lab-03-virtual-memory-dma-iommu/lab-03-virtual-memory-dma-iommu.md) | 源码可完成 | 内存路径图 |
| 4 | [Session 04](../sessions/session-04-pcie-interrupt-device-model/session-04-pcie-interrupt-device-model.md) | PCIe、中断、设备模型 | [Lab 04](../labs/lab-04-pcie-interrupt-device-model/lab-04-pcie-interrupt-device-model.md) | 源码可完成 | 设备初始化流程图 |
| 5 | [Session 05](../sessions/session-05-ioctl-mmap-driver-basics/session-05-ioctl-mmap-driver-basics.md) | `ioctl`、`mmap`、驱动基础 | [Lab 05](../labs/lab-05-ioctl-mmap-driver-basics/lab-05-ioctl-mmap-driver-basics.md) | QEMU 可完成 | 调用链笔记 |
| 6 | [Session 06](../sessions/session-06-graphics-pipeline/session-06-graphics-pipeline.md) | GPU 图形流水线 | [Lab 06](../labs/lab-06-graphics-pipeline/lab-06-graphics-pipeline.md) | 源码可完成 | 流水线图 |
| 7 | [Session 07](../sessions/session-07-compute-model-and-queues/session-07-compute-model-and-queues.md) | GPU 计算模型、User-Mode Queues | [Lab 07](../labs/lab-07-compute-model-and-queues/lab-07-compute-model-and-queues.md) | 源码可完成 | command buffer 笔记 |
| 8 | [Session 08](../sessions/session-08-mesa-libdrm-drm/session-08-mesa-libdrm-drm.md) | Mesa、libdrm、DRM 关系 | [Lab 08](../labs/lab-08-mesa-libdrm-drm/lab-08-mesa-libdrm-drm.md) | 源码可完成 | 用户态图形栈总结 |
| 9 | [Session 09](../sessions/session-09-drm-kms-object-model/session-09-drm-kms-object-model.md) | DRM/KMS 对象模型 | [Lab 09](../labs/lab-09-drm-kms-object-model/lab-09-drm-kms-object-model.md) | QEMU 可完成 | 对象关系图 |
| 10 | [Session 10](../sessions/session-10-atomic-modeset-and-igt/session-10-atomic-modeset-and-igt.md) | Atomic modeset | [Lab 10](../labs/lab-10-atomic-modeset-and-igt/lab-10-atomic-modeset-and-igt.md) | QEMU 可完成 | IGT 测试与日志分析 |
| 11 | [Session 11](../sessions/session-11-gem-ttm-dma-buf/session-11-gem-ttm-dma-buf.md) | GEM、TTM、dma-buf | [Lab 11](../labs/lab-11-gem-ttm-dma-buf/lab-11-gem-ttm-dma-buf.md) | 源码可完成 | 显存管理对比 |
| 12 | [Session 12](../sessions/session-12-fence-vblank-irq/session-12-fence-vblank-irq.md) | Fence、vblank、IRQ | [Lab 12](../labs/lab-12-fence-vblank-irq/lab-12-fence-vblank-irq.md) | QEMU 可完成 | 同步机制笔记 |
| 13 | [Session 13](../sessions/session-13-read-vkms/session-13-read-vkms.md) | `vkms` | [Lab 13](../labs/lab-13-read-vkms/lab-13-read-vkms.md) | QEMU 可完成 | 驱动结构总结 |
| 14 | [Session 14](../sessions/session-14-read-simpledrm/session-14-read-simpledrm.md) | `simpledrm` | [Lab 14](../labs/lab-14-read-simpledrm/lab-14-read-simpledrm.md) | QEMU 可完成 | init 流程图 |
| 15 | [Session 15](../sessions/session-15-read-msm-or-panfrost/session-15-read-msm-or-panfrost.md) | `msm` 或 `panfrost` | [Lab 15](../labs/lab-15-read-msm-or-panfrost/lab-15-read-msm-or-panfrost.md) | 源码可完成 | 提交流程笔记 |
| 16 | [Session 16](../sessions/session-16-read-i915-or-xe/session-16-read-i915-or-xe.md) | `i915` 或 `xe` | [Lab 16](../labs/lab-16-read-i915-or-xe/lab-16-read-i915-or-xe.md) | 源码可完成 | 模块结构总结 |
| 17 | [Session 17](../sessions/session-17-read-amdgpu-memory/session-17-read-amdgpu-memory.md) | `amdgpu` 显存管理 | [Lab 17](../labs/lab-17-read-amdgpu-memory/lab-17-read-amdgpu-memory.md) | 源码可完成 | VM/BO 笔记 |
| 18 | [Session 18](../sessions/session-18-read-amdgpu-submission/session-18-read-amdgpu-submission.md) | `amdgpu` 命令提交和调度 | [Lab 18](../labs/lab-18-read-amdgpu-submission/lab-18-read-amdgpu-submission.md) | 源码可完成 | scheduler/fence 笔记 |
| 19 | [Session 19](../sessions/session-19-page-fault-hang-reset/session-19-page-fault-hang-reset.md) | page fault、hang、reset | [Lab 19](../labs/lab-19-page-fault-hang-reset/lab-19-page-fault-hang-reset.md) | 真机优先 | GPU Hang dump 分析 |
| 20 | [Session 20](../sessions/session-20-page-flip-and-display/session-20-page-flip-and-display.md) | page flip、显示输出 | [Lab 20](../labs/lab-20-page-flip-and-display/lab-20-page-flip-and-display.md) | 真机优先 | KMS/vblank 笔记 |
| 21 | [Session 21](../sessions/session-21-trace-debugfs-perf/session-21-trace-debugfs-perf.md) | trace、debugfs、perf | [Lab 21](../labs/lab-21-trace-debugfs-perf/lab-21-trace-debugfs-perf.md) | 真机优先 | 一次调试记录 |
| 22 | [Session 22](../sessions/session-22-end-to-end-ioctl-path/session-22-end-to-end-ioctl-path.md) | 完整读一次 `ioctl` 路径 | [Lab 22](../labs/lab-22-end-to-end-ioctl-path/lab-22-end-to-end-ioctl-path.md) | QEMU 可完成 | 路径解剖笔记 |
| 23 | [Session 23](../sessions/session-23-specialization/session-23-specialization.md) | 选方向深挖 | [Lab 23](../labs/lab-23-specialization/lab-23-specialization.md) | 按方向决定 | 专题计划 |
| 24 | [Session 24](../sessions/session-24-retrospective-and-next-plan/session-24-retrospective-and-next-plan.md) | 总结和复盘 | [Lab 24](../labs/lab-24-retrospective-and-next-plan/lab-24-retrospective-and-next-plan.md) | 任意环境 | 阶段总结 |

## 阶段划分

上面的表格是唯一的逐周执行计划；下面只按能力递进做阶段说明，帮助你理解为什么这些 session 要按这个顺序排。

每个阶段都建议至少产出一份“可复用资产”，例如路径模板、对象解剖表、调试记录或驱动地图。这样 24 周结束后，你得到的不是一组读过的文档，而是一套能继续用于真实驱动阅读的工具箱。

### 第一阶段：Session 01 (环境准备)

目标：把学习环境搭起来，后面所有实验都能重复。

- 安装 Linux 环境，推荐 Ubuntu 或 Debian。
- 准备内核源码、`clangd`、`ctags`、`ripgrep`、`gdb`、`perf`。
- 下载 Mesa 和 `libdrm` 源码，先熟悉目录结构。
- 建立自己的学习笔记模板。

建议输出：

- 一张 Linux 图形栈总览图。
- 一篇环境搭建笔记。

### 第二阶段：Session 02 到 05 (补基础)

目标：补齐理解 GPU 驱动必须用到的系统基础。

重点内容：

- C 语言进阶：结构体、指针、位运算、链表、回调。
- 操作系统基础：虚拟内存、页表、中断、DMA、缓存一致性。
- 计算机体系结构：PCIe、MMU、IOMMU、TLB。
- Linux 内核基础：模块、设备模型、`ioctl`、`mmap`、锁、工作队列。

建议输出：

- 一篇 “用户态到内核态调用路径” 笔记。
- 一篇 “DMA / IOMMU / 中断关系” 笔记。

### 第三阶段：Session 06 到 08 (图形和 GPU 基础)

目标：先搞清楚 GPU 到底在执行什么，以及驱动夹在中间扮演什么角色。

重点内容：

- 图形流水线：顶点、光栅化、片元、输出合并。
- 计算模型：warp/wave、SIMD、SIMT、dispatch。**以及 User-Mode Queues (UMQs) 概念。**
- 图形 API 和驱动关系：OpenGL、Vulkan、EGL、GBM、DRM。
- `command buffer`、`ring buffer`、`queue`、`doorbell` **(重点理解不同 Ring：Graphics / Compute / Copy 的差异)**。
- VRAM、GTT、system memory、BAR 映射。

建议输出：

- 一篇 “GPU 执行模型速记”。
- 一篇 “OpenGL/Vulkan 到内核驱动的数据路径”。

### 第四阶段：Session 09 到 12 (Linux DRM/KMS 核心)

目标：掌握 Linux GPU 驱动最重要的公共框架。

重点内容：

- DRM/KMS 对象：`drm_device`、`connector`、`encoder`、`crtc`、`plane`、`framebuffer`。
- Atomic modesetting。
- GEM、TTM、`dma-buf`。
- `dma_fence`、`sync_file`、vblank、IRQ。

建议阅读目录：

- `drivers/gpu/drm/`
- `drivers/gpu/drm/drm_ioctl.c`
- `drivers/gpu/drm/drm_atomic*`
- `drivers/gpu/drm/drm_gem*`
- `drivers/gpu/drm/drm_vblank.c`
- `include/drm/`

建议输出：

- 一张 DRM/KMS 对象关系图。
- 一篇 GEM / TTM / dma-buf 对比笔记。
- 一篇 atomic modeset 流程笔记。
- 一次 IGT (igt-gpu-tools) 构建与基础测试运行记录。

### 第五阶段：Session 13 到 18 (开始读真实驱动)

目标：从 “知道框架” 过渡到 “能看懂驱动实现”。

建议阅读顺序：

1. `vkms`
2. `simpledrm`
3. `msm` 或 `panfrost`
4. `i915` 或 `xe`
5. `amdgpu`

阅读时每个驱动都回答这几个问题：

- 设备是怎么注册进 DRM 框架的？
- buffer object 是怎么创建和映射的？
- 命令是怎么提交到硬件的？
- 驱动怎样知道任务完成了？
- 出错时怎样 reset 和恢复？

建议输出：

- 每个驱动一份结构总结。
- 每个驱动一张 “初始化 -> 提交 -> 完成” 的流程图。

### 第六阶段：Session 19 到 22 (专题攻坚)

目标：把几个最难也最重要的模块单独吃透。

专题建议：

- 显存管理：VRAM、GTT、页表、迁移、eviction、pin/unpin。
- 调度与同步：scheduler、fence、timeline、hang detect。
- 显示输出：modeset、page flip、vblank、hotplug。
- 地址空间与上下文：GPU VM、context switch、隔离。
- 故障恢复：page fault、timeout、GPU reset。
- 调试手段：tracepoint、debugfs、perf、drm debug log。

建议输出：

- 每个专题一篇问题清单式笔记。
- 至少做一次真实日志分析。

### 第七阶段：Session 23 到 24 (选择方向继续深入)

你可以按兴趣选择一个方向深挖：

- 图形驱动方向：KMS、显示控制器、Mesa、Vulkan/OpenGL 用户态驱动。
- 计算驱动方向：队列、调度、抢占、虚拟内存、同步。
- 移动 GPU 方向：`msm`、`panfrost`、设备树、电源管理。
- PC GPU 方向：`amdgpu`、`i915/xe`、PCIe、固件、复杂显存管理。
- Windows 方向：WDDM、UMD/KMD、DXGK 调度模型。

建议输出：

- 一篇个人阶段总结。
- 一份下一阶段 8 周计划。

## 推荐源码阅读顺序

### Linux 内核

- `drivers/gpu/drm/drm_file.c`
- `drivers/gpu/drm/drm_ioctl.c`
- `drivers/gpu/drm/drm_mode*`
- `drivers/gpu/drm/drm_atomic*`
- `drivers/gpu/drm/drm_gem*`
- `drivers/gpu/drm/drm_vblank.c`
- `drivers/gpu/drm/vkms/`
- `drivers/gpu/drm/simpledrm/`
- `drivers/gpu/drm/msm/` 或 `drivers/gpu/drm/panfrost/`
- `drivers/gpu/drm/i915/` 或 `drivers/gpu/drm/xe/`
- `drivers/gpu/drm/amd/amdgpu/`

### 用户态

- `libdrm` 里与目标驱动相关的 `ioctl` 包装。
- Mesa 中与 winsys、buffer 和 command submission 相关的代码。

## 必须吃透的核心概念

- `DRM`
- `KMS`
- `GEM`
- `TTM`
- `dma-buf`
- `dma_fence`
- `ioctl`
- `mmap`
- `buffer object`
- `GPU virtual memory`
- `ring buffer`
- `command submission`
- `scheduler`
- `page flip`
- `vblank`
- `IRQ`
- `IOMMU`
- `doorbell`
- `reset`
- `hangcheck`

## 24 周结束时应保留的资产

- 一张 Linux 图形栈总览图。
- 一份内核对象阅读模板。
- 一份 DRM/KMS 对象关系图。
- 一份 GEM / TTM / dma-buf 对比笔记。
- 一份 command submission 到 fence completion 的路径图。
- 一份 page flip 到 vblank event 的路径图。
- 一份 trace/debugfs/perf 工具速查表。
- 至少一份完整 ioctl 路径解剖。
- 一份下一阶段 8 周计划。

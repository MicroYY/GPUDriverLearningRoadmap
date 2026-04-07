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

## Session 映射总览

| 周数 | Session | 学习主题 | 关联 Lab | 输出 |
| --- | --- | --- | --- | --- |
| 1 | [Session 01](../sessions/session-01-environment-and-stack/README.md) | 环境准备、图形栈总览 | [Lab 01](../labs/lab-01-environment-and-stack/README.md) | 环境文档和总览图 |
| 2 | [Session 02](../sessions/session-02-c-and-kernel-structures/README.md) | C 和内核常见数据结构 | [Lab 02](../labs/lab-02-c-and-kernel-structures/README.md) | 结构体、链表、锁笔记 |
| 3 | [Session 03](../sessions/session-03-virtual-memory-dma-iommu/README.md) | 虚拟内存、DMA、IOMMU | [Lab 03](../labs/lab-03-virtual-memory-dma-iommu/README.md) | 内存路径图 |
| 4 | [Session 04](../sessions/session-04-pcie-interrupt-device-model/README.md) | PCIe、中断、设备模型 | [Lab 04](../labs/lab-04-pcie-interrupt-device-model/README.md) | 设备初始化流程图 |
| 5 | [Session 05](../sessions/session-05-ioctl-mmap-driver-basics/README.md) | `ioctl`、`mmap`、驱动基础 | [Lab 05](../labs/lab-05-ioctl-mmap-driver-basics/README.md) | 调用链笔记 |
| 6 | [Session 06](../sessions/session-06-graphics-pipeline/README.md) | GPU 图形流水线 | [Lab 06](../labs/lab-06-graphics-pipeline/README.md) | 流水线图 |
| 7 | [Session 07](../sessions/session-07-compute-model-and-queues/README.md) | GPU 计算模型、User-Mode Queues | [Lab 07](../labs/lab-07-compute-model-and-queues/README.md) | command buffer 笔记 |
| 8 | [Session 08](../sessions/session-08-mesa-libdrm-drm/README.md) | Mesa、libdrm、DRM 关系 | [Lab 08](../labs/lab-08-mesa-libdrm-drm/README.md) | 用户态图形栈总结 |
| 9 | [Session 09](../sessions/session-09-drm-kms-object-model/README.md) | DRM/KMS 对象模型 | [Lab 09](../labs/lab-09-drm-kms-object-model/README.md) | 对象关系图 |
| 10 | [Session 10](../sessions/session-10-atomic-modeset-and-igt/README.md) | Atomic modeset | [Lab 10](../labs/lab-10-atomic-modeset-and-igt/README.md) | IGT 测试与日志分析 |
| 11 | [Session 11](../sessions/session-11-gem-ttm-dma-buf/README.md) | GEM、TTM、dma-buf | [Lab 11](../labs/lab-11-gem-ttm-dma-buf/README.md) | 显存管理对比 |
| 12 | [Session 12](../sessions/session-12-fence-vblank-irq/README.md) | Fence、vblank、IRQ | [Lab 12](../labs/lab-12-fence-vblank-irq/README.md) | 同步机制笔记 |
| 13 | [Session 13](../sessions/session-13-read-vkms/README.md) | `vkms` | [Lab 13](../labs/lab-13-read-vkms/README.md) | 驱动结构总结 |
| 14 | [Session 14](../sessions/session-14-read-simpledrm/README.md) | `simpledrm` | [Lab 14](../labs/lab-14-read-simpledrm/README.md) | init 流程图 |
| 15 | [Session 15](../sessions/session-15-read-msm-or-panfrost/README.md) | `msm` 或 `panfrost` | [Lab 15](../labs/lab-15-read-msm-or-panfrost/README.md) | 提交流程笔记 |
| 16 | [Session 16](../sessions/session-16-read-i915-or-xe/README.md) | `i915` 或 `xe` | [Lab 16](../labs/lab-16-read-i915-or-xe/README.md) | 模块结构总结 |
| 17 | [Session 17](../sessions/session-17-read-amdgpu-memory/README.md) | `amdgpu` 显存管理 | [Lab 17](../labs/lab-17-read-amdgpu-memory/README.md) | VM/BO 笔记 |
| 18 | [Session 18](../sessions/session-18-read-amdgpu-submission/README.md) | `amdgpu` 命令提交和调度 | [Lab 18](../labs/lab-18-read-amdgpu-submission/README.md) | scheduler/fence 笔记 |
| 19 | [Session 19](../sessions/session-19-page-fault-hang-reset/README.md) | page fault、hang、reset | [Lab 19](../labs/lab-19-page-fault-hang-reset/README.md) | 抓取与分析 GPU Hang dump |
| 20 | [Session 20](../sessions/session-20-page-flip-and-display/README.md) | page flip、显示输出 | [Lab 20](../labs/lab-20-page-flip-and-display/README.md) | KMS/vblank 笔记 |
| 21 | [Session 21](../sessions/session-21-trace-debugfs-perf/README.md) | trace、debugfs、perf | [Lab 21](../labs/lab-21-trace-debugfs-perf/README.md) | 一次调试记录 |
| 22 | [Session 22](../sessions/session-22-end-to-end-ioctl-path/README.md) | 完整读一次 `ioctl` 路径 | [Lab 22](../labs/lab-22-end-to-end-ioctl-path/README.md) | 路径解剖笔记 |
| 23 | [Session 23](../sessions/session-23-specialization/README.md) | 选方向深挖 | [Lab 23](../labs/lab-23-specialization/README.md) | 专题计划 |
| 24 | [Session 24](../sessions/session-24-retrospective-and-next-plan/README.md) | 总结和复盘 | [Lab 24](../labs/lab-24-retrospective-and-next-plan/README.md) | 阶段总结 |

## 阶段划分

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

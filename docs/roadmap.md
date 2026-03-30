# 24 周学习路线图

## 总目标

这份路线图以 Linux 开源 GPU 驱动栈为主线，帮助你在 24 周内建立下面这些能力：

1. 理解 GPU 驱动在整个图形栈里的位置。
2. 看懂 Linux DRM/KMS 的核心概念和常见对象。
3. 能阅读典型 GPU 驱动源码，例如 `vkms`、`msm`、`i915/xe`、`amdgpu`。
4. 理解显存管理、命令提交、同步、中断、显示输出这些关键机制。
5. 为后续深入图形驱动、计算驱动或内核开发打基础。

## 阶段划分

### 第 1 周：环境准备

目标：把学习环境搭起来，后面所有实验都能重复。

- 安装 Linux 环境，推荐 Ubuntu 或 Debian。
- 准备内核源码、`clangd`、`ctags`、`ripgrep`、`gdb`、`perf`。
- 下载 Mesa 和 `libdrm` 源码，先熟悉目录结构。
- 建立自己的学习笔记模板。

建议输出：

- 一张 Linux 图形栈总览图。
- 一篇环境搭建笔记。

### 第 2 到 5 周：补基础

目标：补齐理解 GPU 驱动必须用到的系统基础。

重点内容：

- C 语言进阶：结构体、指针、位运算、链表、回调。
- 操作系统基础：虚拟内存、页表、中断、DMA、缓存一致性。
- 计算机体系结构：PCIe、MMU、IOMMU、TLB。
- Linux 内核基础：模块、设备模型、`ioctl`、`mmap`、锁、工作队列。

建议输出：

- 一篇 “用户态到内核态调用路径” 笔记。
- 一篇 “DMA / IOMMU / 中断关系” 笔记。

### 第 6 到 8 周：图形和 GPU 基础

目标：先搞清楚 GPU 到底在执行什么，以及驱动夹在中间扮演什么角色。

重点内容：

- 图形流水线：顶点、光栅化、片元、输出合并。
- 计算模型：warp/wave、SIMD、SIMT、dispatch。
- 图形 API 和驱动关系：OpenGL、Vulkan、EGL、GBM、DRM。
- `command buffer`、`ring buffer`、`queue`、`doorbell`。
- VRAM、GTT、system memory、BAR 映射。

建议输出：

- 一篇 “GPU 执行模型速记”。
- 一篇 “OpenGL/Vulkan 到内核驱动的数据路径”。

### 第 9 到 12 周：Linux DRM/KMS 核心

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

### 第 13 到 18 周：开始读真实驱动

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

### 第 19 到 22 周：专题攻坚

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

### 第 23 到 24 周：选择方向继续深入

你可以按兴趣选择一个方向深挖：

- 图形驱动方向：KMS、显示控制器、Mesa、Vulkan/OpenGL 用户态驱动。
- 计算驱动方向：队列、调度、抢占、虚拟内存、同步。
- 移动 GPU 方向：`msm`、`panfrost`、设备树、电源管理。
- PC GPU 方向：`amdgpu`、`i915/xe`、PCIe、固件、复杂显存管理。
- Windows 方向：WDDM、UMD/KMD、DXGK 调度模型。

建议输出：

- 一篇个人阶段总结。
- 一份下一阶段 8 周计划。

## 24 周执行表

| 周数 | 主题 | 输出 |
| --- | --- | --- |
| 1 | 环境准备、图形栈总览 | 环境文档和总览图 |
| 2 | C 和内核常见数据结构 | 结构体、链表、锁笔记 |
| 3 | 虚拟内存、DMA、IOMMU | 内存路径图 |
| 4 | PCIe、中断、设备模型 | 设备初始化流程图 |
| 5 | `ioctl`、`mmap`、驱动基础 | 调用链笔记 |
| 6 | GPU 图形流水线 | 流水线图 |
| 7 | GPU 计算模型、命令提交流程 | command buffer 笔记 |
| 8 | Mesa、libdrm、DRM 关系 | 用户态图形栈总结 |
| 9 | DRM/KMS 对象模型 | 对象关系图 |
| 10 | Atomic modeset | 流程笔记 |
| 11 | GEM、TTM、dma-buf | 显存管理对比 |
| 12 | Fence、vblank、IRQ | 同步机制笔记 |
| 13 | `vkms` | 驱动结构总结 |
| 14 | `simpledrm` | init 流程图 |
| 15 | `msm` 或 `panfrost` | 提交流程笔记 |
| 16 | `i915` 或 `xe` | 模块结构总结 |
| 17 | `amdgpu` 显存管理 | VM/BO 笔记 |
| 18 | `amdgpu` 命令提交和调度 | scheduler/fence 笔记 |
| 19 | page fault、hang、reset | 故障恢复笔记 |
| 20 | page flip、显示输出 | KMS/vblank 笔记 |
| 21 | trace、debugfs、perf | 一次调试记录 |
| 22 | 完整读一次 `ioctl` 路径 | 路径解剖笔记 |
| 23 | 选方向深挖 | 专题计划 |
| 24 | 总结和复盘 | 阶段总结 |

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

# 面向 GPU 驱动开发者的源码阅读 Checklist

当你进入一个陌生的 GPU 驱动目录（例如 `drivers/gpu/drm/v3d/` 或 `i915/`）或者 DRM 核心模块时，不要漫无目的地顺着行数读。试着拿着以下清单，逐一在源码中寻找答案。当你能把这 8 个问题都填满并解释清楚时，这个模块的代码骨架你就已经完全掌握了。

## Part 1: 驱动的入口与挂载 (Driver Initialization)
- [ ] 该驱动所对应的硬件总线是什么？（PCIe? Platform Device? USB?）
- [ ] 设备的 `.probe` 函数入口在哪里？
- [ ] 驱动是如何分配并初始化核心容器 `struct drm_device` 对象的？
- [ ] 驱动向子系统注册的 `struct drm_driver` 实例化对象叫什么名字？注册函数调用了什么（比如 `drm_dev_register`）？

## Part 2: 文件操作与系统调用 (File Ops & IOCTLs)
- [ ] `open()` 时，驱动有没有分配特定于该 file 进程的 `driver_priv` 结构？（很多上下文相关的逻辑都在这里初始化）
- [ ] 驱动私有的 `ioctl` 编号是通过哪一个全局数组分配的？(定位 `DRM_IOCTL_DEF_DRV` 宏包裹的数组)
- [ ] 找到该驱动用于分配显存/提交命令的私有 `ioctl` 对应的处理函数，它的入参是什么？
- [ ] 驱动支持 `mmap` 的 `.mmap` 接口是指向原生 `drm_gem_mmap` 还是驱动自己包裹了一层？

## Part 3: 显存管理者 (GEM / TTM Backend)
- [ ] 该驱动的 Buffer Object 在 C 中被封装成了什么结构体？（通常是包含 `struct drm_gem_object` 的子类，如 `v3d_bo`）。
- [ ] 它使用了 TTM，还是单独用了基于 GEM 的简单内存分配器？（如 SHMEM helpers，DMA-helpers）
- [ ] `DRM_IOCTL_MODE_CREATE_DUMB` 创建缓冲区时，是哪个函数在做实际的物理内存页分配？

## Part 4: 渲染/计算流水线的灵魂 - 命令提交 (Command Submission)
- [ ] 用户态应用构建好的 ring_buffer 或是 command_stream 是通过具体的哪个 ioctl 函数穿透进内核的？
- [ ] 内核在收到 command stream 后，是否做了安全性校验（Security Validation / Parsing）？
- [ ] 这个驱动使用了 DRM Scheduler 吗 (搜 `drm_sched_entity`)？还是自带了底层的硬件调度器？
- [ ] 提交给实际硬件寄存器 (Kick / Ring Doorbells) 触发执行的具体写寄存器动作，是在哪一行的 `writel()` 中完成的？

## Part 5: 同步与中断 (Sync & IRQs)
- [ ] 这个设备的中断处理程序 (IRQ Handler) 叫什么名字？
- [ ] 命令执行完成 (Job Done) 时，是硬件中断告知 CPU 的，还是 CPU 自己 polling 去检查完成状态寄存器的？
- [ ] 驱动是如何调用 `dma_fence_signal()` 来通知等待这一帧的进程任务已结清的？
- [ ] 如果 GPU Hang 住了发生超时，该驱动的 `.timeout_job` 或 Reset 重置流入口点在哪里？
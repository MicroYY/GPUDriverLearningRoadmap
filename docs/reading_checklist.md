# 面向 GPU 驱动开发者的源码阅读 Checklist

当你进入一个陌生的 GPU 驱动目录（例如 `drivers/gpu/drm/v3d/` 或 `i915/`）或者 DRM 核心模块时，不要漫无目的地顺着行数读。试着拿着以下清单，逐一在源码中寻找答案。当你能把这些问题逐步填满并解释清楚时，这个模块的代码骨架你就已经基本掌握了。

## 使用方式

- 第一次读一个驱动时，先填 Part 1 到 Part 3，建立“入口、对象、内存”的地图。
- 第二次读时再补 Part 4 和 Part 5，追命令提交、同步、中断和恢复路径。
- 如果读的是显示驱动或 KMS 路径，重点补 Part 6。
- 如果读的是复杂 PC GPU 驱动，Part 7 和 Part 8 很重要。
- 每个问题都尽量写出源码文件、函数名、关键结构体和你自己的结论。
- 不要求一次填满。留空的问题就是下一次 session 或 lab 的切入点。

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

## Part 6: 显示与 KMS (Display / KMS)
- [ ] 这个驱动是否实现 KMS？如果实现，connector、crtc、plane、encoder 分别在哪里创建？
- [ ] 驱动使用了哪些 helper？例如 atomic helper、simple display pipe helper、bridge/panel helper。
- [ ] `atomic_check` 和 `atomic_commit` 相关回调在哪里？
- [ ] page flip event 或 vblank event 是在哪条路径里发送给用户态的？
- [ ] 驱动支持哪些 framebuffer format 和 modifier？这些限制在哪里检查？

## Part 7: 地址空间与 VM (Memory / VM)
- [ ] BO 的 GPU virtual address 在哪里分配或传入？
- [ ] BO 是在哪里 bind / map 到 GPU VM 的？
- [ ] 页表更新是 CPU 直接完成，还是通过 GPU job 完成？
- [ ] 如果发生 GPU page fault，日志里有哪些地址、VMID、PASID、engine 或进程信息？
- [ ] IOMMU/SMMU 和 GPU VM 在这个驱动里分别出现在哪里？

## Part 8: 运行时证据 (Runtime Evidence)
- [ ] 这个驱动有哪些 `debugfs` 节点？对应源码里的 `seq_file` 或 debugfs 注册入口在哪里？
- [ ] 有哪些 tracepoint 可以观察 submit、fence、vblank、reset 或 fault？
- [ ] IGT 或其他测试里有没有覆盖这条路径的用例？
- [ ] 一次运行记录能否对应到至少一个源码函数和一个核心对象？
- [ ] 当前结论里哪些来自源码，哪些来自运行日志，哪些仍然只是推测？

## 推荐记录格式

```text
驱动或模块：
本次阅读目标：
入口函数：
核心对象：
关键 ioctl / mmap / submit 路径：
同步与完成路径：
显示/KMS路径：
内存/VM路径：
调试入口：
我已经确认的结论：
还只是推测的判断：
下次继续追的问题：
```

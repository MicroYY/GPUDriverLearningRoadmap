# Session 导航

这个仓库现在以 session 为主组织学习内容。你可以把每个 session 理解成一周或一个明确主题块的学习单元。

每个 session 的职责是回答“这一周要理解什么、读哪些入口、最后应该能解释什么”。真正动手、追路径、跑命令或整理证据时，进入同号 lab。

## 推荐顺序

1. [Session 01：环境准备与图形栈总览](session-01-environment-and-stack/session-01-environment-and-stack.md)
2. [Session 02：C 与内核数据结构](session-02-c-and-kernel-structures/session-02-c-and-kernel-structures.md)
3. [Session 03：虚拟内存、DMA、IOMMU](session-03-virtual-memory-dma-iommu/session-03-virtual-memory-dma-iommu.md)
4. [Session 04：PCIe、中断与设备模型](session-04-pcie-interrupt-device-model/session-04-pcie-interrupt-device-model.md)
5. [Session 05：`ioctl`、`mmap` 与驱动基础](session-05-ioctl-mmap-driver-basics/session-05-ioctl-mmap-driver-basics.md)
6. [Session 06：GPU 图形流水线](session-06-graphics-pipeline/session-06-graphics-pipeline.md)
7. [Session 07：GPU 计算模型与队列](session-07-compute-model-and-queues/session-07-compute-model-and-queues.md)
8. [Session 08：Mesa、libdrm、DRM 关系](session-08-mesa-libdrm-drm/session-08-mesa-libdrm-drm.md)
9. [Session 09：DRM/KMS 对象模型](session-09-drm-kms-object-model/session-09-drm-kms-object-model.md)
10. [Session 10：Atomic modeset 与 IGT 基础](session-10-atomic-modeset-and-igt/session-10-atomic-modeset-and-igt.md)
11. [Session 11：GEM、TTM、dma-buf](session-11-gem-ttm-dma-buf/session-11-gem-ttm-dma-buf.md)
12. [Session 12：Fence、vblank、IRQ](session-12-fence-vblank-irq/session-12-fence-vblank-irq.md)
13. [Session 13：阅读 `vkms`](session-13-read-vkms/session-13-read-vkms.md)
14. [Session 14：阅读 `simpledrm`](session-14-read-simpledrm/session-14-read-simpledrm.md)
15. [Session 15：阅读 `msm` 或 `panfrost`](session-15-read-msm-or-panfrost/session-15-read-msm-or-panfrost.md)
16. [Session 16：阅读 `i915` 或 `xe`](session-16-read-i915-or-xe/session-16-read-i915-or-xe.md)
17. [Session 17：阅读 `amdgpu` 显存管理](session-17-read-amdgpu-memory/session-17-read-amdgpu-memory.md)
18. [Session 18：阅读 `amdgpu` 命令提交和调度](session-18-read-amdgpu-submission/session-18-read-amdgpu-submission.md)
19. [Session 19：Page fault、Hang 与 Reset](session-19-page-fault-hang-reset/session-19-page-fault-hang-reset.md)
20. [Session 20：Page flip 与显示输出](session-20-page-flip-and-display/session-20-page-flip-and-display.md)
21. [Session 21：Trace、debugfs、perf](session-21-trace-debugfs-perf/session-21-trace-debugfs-perf.md)
22. [Session 22：完整读一次 `ioctl` 路径](session-22-end-to-end-ioctl-path/session-22-end-to-end-ioctl-path.md)
23. [Session 23：选方向深挖](session-23-specialization/session-23-specialization.md)
24. [Session 24：总结与下一阶段计划](session-24-retrospective-and-next-plan/session-24-retrospective-and-next-plan.md)

## 使用方式

- 先看 [docs/roadmap.md](../docs/roadmap.md)，再按 session 顺序推进。
- 需要动手时，进入同号 lab，例如 Session 09 对应 Lab 09。
- 每完成一个 session，用 [docs/weekly-template.md](../docs/weekly-template.md) 记一次复盘。
- 如果某个 session 需要真实硬件或只适合源码阅读，优先参考 [docs/roadmap.md](../docs/roadmap.md) 的环境标签。

## 建议阅读节奏

1. 先读“目标”和“核心问题”，确认这一节要解决的主线。
2. 再看“建议输出”，把输出当作本周验收标准。
3. 最后打开关联 lab，把输出落成笔记、图、源码路径或运行记录。

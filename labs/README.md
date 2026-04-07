# Labs 导航

lab 的目标不是做题，而是把抽象概念落实到真实源码、日志和实验结果上。

## Lab 索引

1. [Lab 01：环境准备与图形栈总览](lab-01-environment-and-stack/README.md)
2. [Lab 02：C 与内核数据结构](lab-02-c-and-kernel-structures/README.md)
3. [Lab 03：虚拟内存、DMA、IOMMU](lab-03-virtual-memory-dma-iommu/README.md)
4. [Lab 04：PCIe、中断与设备模型](lab-04-pcie-interrupt-device-model/README.md)
5. [Lab 05：`ioctl`、`mmap` 与驱动基础](lab-05-ioctl-mmap-driver-basics/README.md)
6. [Lab 06：GPU 图形流水线](lab-06-graphics-pipeline/README.md)
7. [Lab 07：GPU 计算模型与队列](lab-07-compute-model-and-queues/README.md)
8. [Lab 08：Mesa、libdrm、DRM 关系](lab-08-mesa-libdrm-drm/README.md)
9. [Lab 09：DRM/KMS 对象模型](lab-09-drm-kms-object-model/README.md)
10. [Lab 10：Atomic modeset 与 IGT 基础](lab-10-atomic-modeset-and-igt/README.md)
11. [Lab 11：GEM、TTM、dma-buf](lab-11-gem-ttm-dma-buf/README.md)
12. [Lab 12：Fence、vblank、IRQ](lab-12-fence-vblank-irq/README.md)
13. [Lab 13：阅读 `vkms`](lab-13-read-vkms/README.md)
14. [Lab 14：阅读 `simpledrm`](lab-14-read-simpledrm/README.md)
15. [Lab 15：阅读 `msm` 或 `panfrost`](lab-15-read-msm-or-panfrost/README.md)
16. [Lab 16：阅读 `i915` 或 `xe`](lab-16-read-i915-or-xe/README.md)
17. [Lab 17：阅读 `amdgpu` 显存管理](lab-17-read-amdgpu-memory/README.md)
18. [Lab 18：阅读 `amdgpu` 命令提交和调度](lab-18-read-amdgpu-submission/README.md)
19. [Lab 19：Page fault、Hang 与 Reset](lab-19-page-fault-hang-reset/README.md)
20. [Lab 20：Page flip 与显示输出](lab-20-page-flip-and-display/README.md)
21. [Lab 21：Trace、debugfs、perf](lab-21-trace-debugfs-perf/README.md)
22. [Lab 22：完整读一次 `ioctl` 路径](lab-22-end-to-end-ioctl-path/README.md)
23. [Lab 23：选方向深挖](lab-23-specialization/README.md)
24. [Lab 24：总结与下一阶段计划](lab-24-retrospective-and-next-plan/README.md)

## 建议完成方式

- 每个 lab 都要留下实验记录。
- 每个 lab 都尽量附上源码路径、关键函数和自己的结论。
- 如果有流程图或补充说明，可以直接附在对应 session 的复盘中。

## 与 roadmap 和 sessions 的关系

- 每个 session 现在都对应一个单独的 lab。
- lab 编号与 session 编号保持一致。
- 最推荐的使用方式是：先读 session，再做同号 lab。

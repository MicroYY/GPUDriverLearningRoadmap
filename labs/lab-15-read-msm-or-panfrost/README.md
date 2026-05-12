# Lab 15：阅读 `msm` 或 `panfrost`

## 对应 Session

- [Session 15：阅读 `msm` 或 `panfrost`](../../sessions/session-15-read-msm-or-panfrost/README.md)

## 目标

观察移动 GPU 驱动中的提交流程与对象组织。

## 开始前先确认

- 已经完成 Session 15。
- 在 `msm` 和 `panfrost` 中选择一个作为主线。
- 没有对应硬件时，本 lab 以源码路径追踪为主。

## 任务

### 1. 找到命令提交 ioctl 或入口函数

记录：

- ioctl 表或 submit 入口。
- 参数结构体。
- GEM / BO 查找路径。
- job 创建位置。

建议命令：

```bash
rg -n "DRM_IOCTL_DEF_DRV|submit|gem_submit|drm_sched|job|mmu|irq" drivers/gpu/drm/msm drivers/gpu/drm/panfrost
```

### 2. 记录 scheduler / ring / queue 相关对象

至少找出：

- job 对象。
- scheduler entity。
- ring 或 queue。
- fence。
- IRQ 或完成回调。

### 3. 画一张提交路径图

从用户态提交画到 job 入队或硬件 kick。

如果没有真实硬件，在图上标注“源码可确认”和“需要硬件验证”的节点。

### 4. 补一张 platform 资源表

```text
驱动：
probe：
MMIO resource：
IRQ：
clock / reset / regulator：
runtime PM：
IOMMU / MMU：
submit ioctl：
fault / reset 入口：
```

## 交付物

- 提交流程笔记
- 驱动结构总结
- platform 资源表

## 检查项

- [ ] 我只选择了一个主线驱动。
- [ ] 我找到 submit 入口和 job 对象。
- [ ] 我能说明移动 GPU 驱动与 PC GPU 驱动的一个架构差异。
- [ ] 我标注了哪些结论来自源码、哪些需要硬件验证。

## 完成标准

- 你能在没有完全理解所有细节的情况下，仍然画出一个真实驱动的命令提交流程骨架。

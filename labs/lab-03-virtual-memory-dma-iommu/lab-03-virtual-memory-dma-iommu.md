# Lab 03：虚拟内存、DMA、IOMMU

## 对应 Session

- [Session 03：虚拟内存、DMA、IOMMU](../../sessions/session-03-virtual-memory-dma-iommu/session-03-virtual-memory-dma-iommu.md)

## 目标

建立 CPU、设备、IOMMU 与地址转换的统一视角。

## 开始前先确认

- 已经准备 Linux kernel 源码。
- 已经完成 Session 03 的核心概念阅读。
- 当前 lab 可以只做源码阅读，不强制要求真实 GPU。

## 任务

### 1. 画地址空间关系图

图里至少包含：

- CPU virtual address
- physical address
- DMA address / IOVA
- GPU virtual address
- IOMMU
- system memory 或 VRAM

### 2. 阅读一条 DMA mapping 路径

优先从这些入口里选一个：

- `dma_map_page`
- `dma_map_sg`
- `dma_alloc_coherent`
- DRM GEM DMA helper 相关路径

可以用下面的命令定位：

```bash
rg -n "dma_map_page|dma_map_sg|dma_map_sgtable|dma_alloc_coherent|dma_unmap" include kernel drivers/gpu drivers/dma-buf
```

记录调用链中的关键函数和你理解的地址变化。

### 3. 解释 IOMMU 的作用

用自己的话回答：

- 没有 IOMMU 时，设备看到的地址是什么？
- 有 IOMMU 后，设备访问为什么更容易隔离？
- GPU VM 和 IOMMU 是不是同一个东西？

### 4. 解剖一个 BO 的地址身份

任选一个 GEM/BO 相关结构体，写下它可能拥有的地址或引用：

```text
CPU virtual address：
physical page / struct page：
DMA address / IOVA：
GPU virtual address：
GEM handle：
dma-buf fd：
mmap offset：
```

不要求每一项都在同一个对象里找到，但要说明缺失项为什么不存在或本周没追到。

## 交付物

- 内存路径图
- DMA / IOMMU 笔记
- BO 地址身份表

## 检查项

- [ ] 我能区分 CPU virtual address、physical address、DMA address 和 GPU virtual address。
- [ ] 我找到至少一条 DMA mapping 相关源码路径。
- [ ] 我能解释 IOMMU 的隔离和地址转换作用。
- [ ] 我能说明 GPU VM 和 IOMMU 不是同一层地址翻译。

## 完成标准

- 你能看到一个 BO 或 DMA buffer 时，知道它可能同时处在多个地址空间里。

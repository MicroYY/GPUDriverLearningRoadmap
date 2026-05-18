# Session 16：阅读 `i915` 或 `xe`

## 目标

理解 Intel PC GPU 驱动的模块组织方式，并开始追踪 GEM / BO / VM / context 等核心对象的生命周期。

## 核心问题

- 复杂驱动如何拆分模块和对象？
- BO / GEM 生命周期在驱动中是如何体现的？
- `i915` 和 `xe` 应该如何选择阅读主线？

## 学习内容

### 1. i915 和 xe 应该怎么选

`i915` 是历史很长、覆盖大量 Intel GPU 的成熟驱动；`xe` 是较新的 Intel DRM 驱动，面向更新的架构和更现代的内部组织方式。学习时不需要同时深挖两者。

可以这样选择：

- 如果你的目标是理解大量现存系统、历史路径和经典 Intel DRM 实现，选 `i915`。
- 如果你的目标是看较新的驱动组织、GT/tile/VM/exec 模型，选 `xe`。
- 如果你有对应 Intel 硬件，优先选当前内核实际加载的驱动。
- 如果只是源码学习，优先选择目录结构更容易让你持续推进的一方。

这节的核心不是背 Intel 细节，而是学习如何读大型 PC GPU 驱动。

### 2. 大型驱动要先画地图

`i915` 和 `xe` 都不是适合从第一行一路读到最后一行的驱动。第一轮只做地图：

```bash
find drivers/gpu/drm/i915 -maxdepth 2 -type d | sort
find drivers/gpu/drm/xe -maxdepth 2 -type d | sort
```

然后按职责分组：

```text
设备入口：PCI probe / driver load
核心设备：drm_device 私有结构、GT/tile
内存对象：GEM/BO、TTM、placement
地址空间：VM、page table、bind
执行上下文：context、engine、queue
提交：exec ioctl、scheduler、fence
显示：display/KMS 目录
调试：debugfs、trace、selftest
```

大型驱动最怕“看见一个函数就追到底”。先知道模块边界，后面追路径才不会失控。

### 3. i915 的几个阅读锚点

如果选 `i915`，先找这些概念：

- `struct drm_i915_private`
  驱动私有设备总对象，通常是理解全局状态的入口。

- GEM object
  Intel buffer object 的核心抽象，围绕创建、pin、bind、mmap、释放展开。

- GT / engine
  GPU 执行单元和 engine 管理相关路径。

- context / request
  提交和执行上下文相关对象。

- display
  i915 里显示路径也很大，初学时可以先和渲染提交主线分开。

可用命令：

```bash
rg -n "struct drm_i915_private|i915_driver_probe|gem_create|i915_gem_object" drivers/gpu/drm/i915
```

第一轮目标是能指出：设备入口、BO 创建入口、执行提交入口、fence/request 完成入口分别在哪里。

### 4. xe 的几个阅读锚点

如果选 `xe`，优先建立这些对象的关系：

- `xe_device`
  驱动设备核心对象。

- tile / GT
  新硬件上可能有 tile 概念，GT 表示图形技术块或执行相关单元。

- `xe_bo`
  buffer object。

- `xe_vm`
  GPU 虚拟地址空间。

- exec queue
  提交队列和执行上下文。

可用命令：

```bash
rg -n "struct xe_device|struct xe_bo|struct xe_vm|exec|queue" drivers/gpu/drm/xe
```

读 `xe` 时，尤其要关注 BO 与 VM 绑定、exec 参数、syncobj/fence 的关系。

### 5. 追一个 BO 生命周期

不管选哪个驱动，本节最好只追一个 BO 生命周期。

标准问题：

```text
用户态如何请求创建 BO？
内核 handler 在哪里？
驱动私有 BO 结构体叫什么？
它是否嵌入 drm_gem_object 或 ttm_buffer_object？
handle 在哪里创建？
CPU mmap 路径在哪里？
GPU VM bind 路径在哪里？
引用计数在哪里增加和释放？
对象释放最终走到哪个函数？
```

一个抽象对象关系可以这样写：

```c
struct intel_like_bo {
    struct drm_gem_object gem;
    struct ttm_buffer_object ttm;
    struct dma_resv *resv;
    /* driver private placement, cache, VM binding state */
};
```

真实结构体不一定长这样，但你要找的角色就是：GEM 接入 DRM，TTM 或私有内存管理处理放置，reservation/fence 处理同步。

### 6. 追大型驱动时怎么避免迷路

每次只选一条路径，例如：

- BO 创建。
- VM bind。
- command submit。
- fence completion。
- page flip。

每条路径只做三层深度：

1. 用户态或 DRM core 入口。
2. 驱动私有 handler。
3. 核心对象和关键回调。

不要第一轮就追所有 helper、所有硬件代际分支、所有 workqueue。大型驱动里的条件编译、平台差异、硬件 workaround 很多，初学阶段先建立“主干”和“支线”的区别。

### 7. 本节实践：做一张模块地图

记录模板：

```text
选择驱动：i915 / xe
设备入口：
核心 device 结构：
BO 结构：
VM 结构：
context / queue 结构：
engine / GT 结构：
submit ioctl：
fence/request 对象：
debugfs/trace 入口：
本周只深入的一条路径：
暂时跳过的复杂分支：
```

这张图会成为后续读 `amdgpu` 或其他复杂驱动的参照。

## 建议源码入口

- `drivers/gpu/drm/i915/`
- `drivers/gpu/drm/xe/`
- `drivers/gpu/drm/i915/i915_driver.c`
- `drivers/gpu/drm/i915/gem/`
- `drivers/gpu/drm/xe/xe_device.c`
- `drivers/gpu/drm/xe/xe_bo.c`

## 建议输出

- 模块结构总结
- BO 生命周期入口列表

## 完成标准

- 能画出所选驱动的主要子目录和职责。
- 能指出一个 BO / GEM object 的创建和释放入口。
- 能说明复杂驱动中“先画地图再追细节”的阅读策略。

## 关联 Lab

- [Lab 16：阅读 `i915` 或 `xe`](../../labs/lab-16-read-i915-or-xe/lab-16-read-i915-or-xe.md)

## 下一步

进入 Session 17，把阅读焦点转向 `amdgpu` 的显存管理和 GPU VM。

# Session 11：GEM、TTM、dma-buf

## 目标

理解 Linux GPU 驱动中 buffer object 的公共抽象、复杂显存管理框架和跨设备共享机制。

## 核心问题

- GEM 和 TTM 分别适合什么场景？
- `dma-buf` 如何在驱动之间共享对象？
- 为什么显存管理既是内存问题，也是对象生命周期问题？

## 学习内容

### 1. Buffer object 是 GPU 驱动的核心资产

GPU 要处理的数据几乎都落在 buffer object 上：

- vertex buffer、index buffer。
- texture、render target。
- command buffer。
- shader binary。
- scanout framebuffer。
- compute 输入输出数据。

所以显存管理不是“分配一块内存”这么简单，而是要回答：

- 这块 buffer 在哪里：system memory、VRAM、GTT、stolen memory？
- 谁在引用它：哪个进程、哪个 fd、哪个 dma-buf、哪个 GPU VM？
- 谁正在使用它：render、compute、display、copy engine？
- 它能不能迁移、驱逐、pin、mmap、共享？

Session 11 的目标就是把 GEM、TTM、dma-buf 三个名字放到这套问题里。

### 2. GEM：DRM 里的 buffer object 公共抽象

GEM 可以先理解为 DRM 提供的一套 buffer object 基础设施。一个驱动 BO 常常会嵌入 `struct drm_gem_object`：

```c
struct my_bo {
    struct drm_gem_object base;
    struct sg_table *sgt;
    u64 gpu_va;
    bool scanout;
};

static inline struct my_bo *to_my_bo(struct drm_gem_object *obj)
{
    return container_of(obj, struct my_bo, base);
}
```

GEM 帮驱动处理很多通用问题：

- 对象引用计数。
- handle 创建和查找。
- mmap offset 管理。
- PRIME/dma-buf 共享入口。
- dumb buffer 等公共路径。

但 GEM 本身不等于完整显存管理器。复杂 GPU 还需要处理多内存域、迁移和 eviction，这就是 TTM 经常出现的地方。

### 3. Dumb buffer 是入门观察 GEM/KMS 的好入口

dumb buffer 是 KMS 提供的简单 framebuffer 分配接口，常用于不依赖 3D 加速的显示测试。

用户态大致会这样：

```c
struct drm_mode_create_dumb create = {
    .width = width,
    .height = height,
    .bpp = 32,
};

ioctl(fd, DRM_IOCTL_MODE_CREATE_DUMB, &create);

struct drm_mode_map_dumb map = {
    .handle = create.handle,
};
ioctl(fd, DRM_IOCTL_MODE_MAP_DUMB, &map);

void *ptr = mmap(NULL, create.size, PROT_READ | PROT_WRITE,
                 MAP_SHARED, fd, map.offset);
```

这条路径非常适合把 Session 05 的 ioctl/mmap 和本节的 GEM object 连起来：

- create dumb 创建 BO 并返回 GEM handle。
- map dumb 返回 fake offset。
- mmap 把 BO 映射到用户态。
- AddFB2 把这个 BO 包装成 KMS framebuffer。

### 4. TTM：处理复杂显存放置和迁移

TTM 主要用于更复杂的 GPU 显存管理场景，特别是有 VRAM、GTT、system memory 多种放置位置的设备。

它解决的问题包括：

- placement：对象可以放在哪些内存域。
- validate：使用前确保对象在合适位置。
- eviction：显存不够时驱逐对象。
- migration：在 VRAM 和 system memory/GTT 之间移动对象。
- reservation：用 `dma_resv` 管理共享访问和 fence。

一个简化的放置模型可以这样理解：

```c
static const struct ttm_place placements[] = {
    { .mem_type = TTM_PL_VRAM, .flags = 0 },
    { .mem_type = TTM_PL_TT,   .flags = 0 },
};

struct ttm_placement placement = {
    .num_placement = ARRAY_SIZE(placements),
    .placement = placements,
};
```

真实驱动会根据 BO 类型、是否 scanout、CPU 是否频繁访问、是否需要 visible VRAM 等条件决定 placement。

读 `amdgpu_bo` 时，TTM 是绕不开的；读简单驱动时，GEM helper 可能已经足够。

### 5. dma-buf：跨设备共享 buffer 的 fd

`dma-buf` 解决的是跨驱动共享 buffer 的问题。比如：

- GPU 渲染一帧。
- 显示控制器 scanout 这帧。
- 视频编码器读取这帧。
- 相机或解码器产出的 buffer 被 GPU 采样。

共享时，用户态拿到的是一个 fd：

```c
int dma_buf_fd;

drmPrimeHandleToFD(fd, gem_handle, DRM_CLOEXEC, &dma_buf_fd);
```

另一个驱动或进程可以导入：

```c
uint32_t imported_handle;

drmPrimeFDToHandle(other_fd, dma_buf_fd, &imported_handle);
```

内核侧的关键是 exporter/importer 协作：

- exporter 拥有真实 backing storage。
- importer 通过 dma-buf attachment 建立自己设备可访问的映射。
- `dma_resv` 和 fence 用来表达谁正在读写这个共享 buffer。

### 6. handle、dma-buf fd、GPU VA、CPU mmap 的区别

同一个 BO 可能有多种“名字”：

```text
GEM handle     -> 某个 DRM fd 内的对象引用
dma-buf fd     -> 跨进程/跨驱动共享引用
fake mmap offset -> 用户态 mmap 时查找对象
GPU VA         -> GPU 命令或 shader 访问它的地址
CPU pointer    -> mmap/vmap 后 CPU 访问它的地址
```

这些名字不是互相替代的。读 bug 时如果只写“buffer 地址不对”，通常还不够精确。要说明是哪一种地址或引用出了问题。

### 7. reservation object 和 fence

共享 buffer 最难的地方不是 fd，而是同步。一个 buffer 可能正在被 GPU 写，同时另一个设备想读。Linux 用 `dma_resv` 关联 fence，表达这个对象当前有哪些未完成访问。

简化理解：

```text
BO
  -> dma_resv
       -> exclusive/write fence
       -> shared/read fences
```

提交新 job 前，驱动会收集依赖 fence；提交后，把新的 fence 挂回 BO 的 reservation object。这样其他使用者可以等待正确的完成点。

这部分会和 Session 12 的 `dma_fence` 紧密连接。

### 8. 本节实践：追一个 BO 的生命周期

选择一个简单入口，例如 dumb buffer 或目标驱动的 create BO ioctl：

```bash
rg -n "dumb_create|gem_create|bo_create|drm_gem_handle_create" drivers/gpu/drm
```

按下面模板记录：

```text
创建 ioctl：
内核对象结构体：
是否嵌入 drm_gem_object：
backing storage：
handle 创建位置：
mmap offset 创建位置：
是否支持 dma-buf export/import：
是否使用 TTM：
释放路径：
```

完成这张表以后，再读复杂的 `amdgpu_bo` 或 `i915_gem_object` 就不会只看到一堆字段。

## 建议源码入口

- `include/drm/drm_gem.h`
- `drivers/gpu/drm/drm_gem.c`
- `drivers/gpu/drm/drm_prime.c`
- `drivers/gpu/drm/ttm/`
- `drivers/dma-buf/`
- `include/linux/dma-buf.h`

## 建议输出

- GEM / TTM / dma-buf 对比笔记

## 完成标准

- 能解释 GEM、TTM、`dma-buf` 各自解决的问题。
- 能指出一个 BO 的创建、导出或映射入口。
- 能说明 handle 和 fd 在用户态/内核态对象引用中的差异。

## 关联 Lab

- [Lab 11：GEM、TTM、dma-buf](../../labs/lab-11-gem-ttm-dma-buf/lab-11-gem-ttm-dma-buf.md)

## 下一步

进入 Session 12，把 buffer 和提交结果如何同步、如何被中断和 vblank 驱动继续串起来。

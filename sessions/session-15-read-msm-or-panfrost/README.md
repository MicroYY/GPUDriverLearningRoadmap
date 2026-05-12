# Session 15：阅读 `msm` 或 `panfrost`

## 目标

进入更真实的 SoC / Mobile GPU 驱动实现，观察设备树、平台设备、buffer 管理、命令提交和 scheduler 如何组织在一起。

## 核心问题

- 这些驱动如何组织提交路径？
- 移动端驱动在架构上和 PC GPU 有哪些差异？
- 没有对应硬件时，源码阅读应该优先追哪些路径？

## 学习内容

### 1. 为什么从移动 GPU 驱动开始读真实提交路径

`msm` 和 `panfrost` 都比 `vkms`、`simpledrm` 更接近真实 GPU 驱动：

- 有真实硬件设备。
- 有 GEM/BO。
- 有 GPU 地址空间或 MMU。
- 有 submit ioctl。
- 有 scheduler/job/fence。
- 有 IRQ 和 reset。
- 有电源管理和平台资源。

但它们通常又比 `amdgpu`、`i915/xe` 小一些，更适合第一次读“真实提交路径”。

本节建议二选一，不要同一周同时深挖两个。你可以按硬件条件选择：有 Qualcomm/Adreno 环境就选 `msm`，对 Arm Mali Midgard/Bifrost/Panfrost 更感兴趣就选 `panfrost`。

### 2. 移动 GPU 和 PC GPU 的第一层差异

移动端 GPU 驱动经常围绕 platform device 展开，而不是 PCIe：

- 设备由 device tree 或 ACPI 描述。
- MMIO、IRQ、clock、reset、power domain 都来自平台资源。
- IOMMU/SMMU 很常见。
- 电源管理、devfreq、runtime PM 非常重要。
- 显存通常不是独立 VRAM，而是 system memory + IOMMU/GPU MMU。

所以读移动 GPU 驱动时，probe 里除了 DRM 初始化，还要认真看：

```text
platform resource
clock / reset / regulator
runtime PM
IOMMU / address space
interrupt
devfreq / opp
```

这些不是外围细节，它们决定 GPU 能不能被上电、访问内存和处理中断。

### 3. 推荐阅读顺序

无论选 `msm` 还是 `panfrost`，都按这个顺序读：

1. 入口：platform driver、probe、remove。
2. DRM device：`drm_device` 和私有设备结构。
3. file private：每个打开进程有什么上下文。
4. GEM/BO：buffer 如何创建、mmap、引用、释放。
5. MMU/VM：buffer 如何映射进 GPU 地址空间。
6. submit ioctl：用户态如何提交 command buffer。
7. scheduler/job：job 如何排队和产生 fence。
8. IRQ：硬件完成后如何 signal fence。
9. reset/fault：出错时从哪里进入恢复。

这个顺序能避免一开始掉进硬件寄存器细节。

### 4. msm 提交路径的阅读提示

如果选择 `msm`，可以从这些关键词入手：

```bash
rg -n "DRM_IOCTL_DEF_DRV|gem_submit|submit|gpu_submit|drm_sched" drivers/gpu/drm/msm
```

你要建立的粗路径是：

```text
用户态 submit ioctl
    -> msm_gem_submit 创建 submit 对象
    -> 查找 BO 和 command buffer
    -> 处理 fence / syncobj 依赖
    -> 绑定到 GPU address space
    -> 创建 scheduler job
    -> 提交到 Adreno ringbuffer
    -> IRQ 完成后 signal fence
```

`msm` 里还要注意 GPU generation 差异。不要试图第一周读懂所有 Adreno 代际代码，先抓住 DRM/GEM/submit/scheduler 的公共骨架。

### 5. panfrost 提交路径的阅读提示

如果选择 `panfrost`，可以从：

```bash
rg -n "DRM_IOCTL_DEF_DRV|submit|drm_sched|job|mmu|gem" drivers/gpu/drm/panfrost
```

粗路径可以这样记：

```text
用户态 submit ioctl
    -> 解析 job 描述
    -> 查找 GEM BO
    -> 准备 MMU 映射
    -> 创建 panfrost job
    -> 进入 DRM scheduler
    -> 写 job slot / doorbell 类寄存器
    -> IRQ 完成或 fault
    -> fence signal / reset
```

`panfrost` 很适合观察 job slot、MMU fault 和 scheduler 的关系。

### 6. 一个真实 submit handler 大概在做什么

用伪代码表示，真实驱动的 submit ioctl 往往像这样：

```c
static int my_gpu_submit_ioctl(struct drm_device *dev, void *data,
                               struct drm_file *file)
{
    struct drm_my_submit *args = data;
    struct my_file *ctx = file->driver_priv;
    struct my_job *job;
    int ret;

    job = my_job_create(ctx, args);
    if (IS_ERR(job))
        return PTR_ERR(job);

    ret = my_lookup_submit_bos(file, job, args);
    if (ret)
        goto err_job;

    ret = my_gpu_vm_bind(job);
    if (ret)
        goto err_job;

    ret = drm_sched_job_init(&job->base, ctx->entity, 1, ctx);
    if (ret)
        goto err_job;

    drm_sched_entity_push_job(&job->base);
    return 0;

err_job:
    my_job_put(job);
    return ret;
}
```

真实代码会更复杂，但核心问题固定：参数、对象、地址空间、依赖、调度、完成。

### 7. 本节实践：只追一条主线

记录模板：

```text
选择驱动：msm / panfrost
platform driver：
probe：
私有 device：
file private：
GEM object：
BO create ioctl：
submit ioctl：
job 结构体：
scheduler entity：
ring/job slot：
IRQ handler：
fence signal：
reset/fault 入口：
```

本节不要求读完整个驱动。能把一条 submit 主线讲清楚，就已经完成目标。

## 建议源码入口

- `drivers/gpu/drm/msm/msm_drv.c`
- `drivers/gpu/drm/msm/msm_gem.c`
- `drivers/gpu/drm/msm/msm_gem_submit.c`
- `drivers/gpu/drm/panfrost/panfrost_drv.c`
- `drivers/gpu/drm/panfrost/panfrost_job.c`
- `drivers/gpu/drm/panfrost/panfrost_gem.c`

## 建议输出

- 提交流程笔记
- 驱动结构总结

## 完成标准

- 能指出所选驱动的 probe、GEM、submit、scheduler 和 IRQ 入口。
- 能画出从用户态提交到 job 入队的大致路径。
- 能说明源码可完成的部分和需要真实硬件验证的部分。

## 关联 Lab

- [Lab 15：阅读 `msm` 或 `panfrost`](../../labs/lab-15-read-msm-or-panfrost/README.md)

## 下一步

进入 Session 16，阅读更复杂的 PC GPU 驱动组织方式。

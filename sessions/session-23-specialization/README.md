# Session 23：选方向深挖

## 目标

根据兴趣、硬件条件和职业目标选择一个具体方向，形成下一阶段可执行的深入路径。

## 核心问题

- 我应该继续横向补知识，还是纵向深入一个驱动？
- 当前硬件和环境能支撑哪个方向的真实验证？
- 下一阶段的每周输出如何避免变成“又看了一些代码”？

## 学习内容

### 1. 为什么这时必须收敛方向

学完前 22 个 session 后，你已经有了 GPU 驱动的主要地图：

```text
用户态图形栈 -> ioctl/mmap -> DRM core
    -> KMS / GEM / TTM / dma-buf
    -> scheduler / fence / IRQ
    -> 具体驱动 / 调试 / 故障恢复
```

下一阶段如果还想同时追所有方向，很容易变成浅尝辄止。Session 23 的任务是把“我知道有哪些模块”转成“我接下来要在一个方向上形成作品级理解”。

选择方向不是永久绑定，而是给未来 4 到 8 周一个清晰主线。

### 2. 可选方向一：图形显示驱动

适合你如果更关心：

- KMS 对象模型。
- atomic commit。
- page flip、vblank、hotplug。
- connector、bridge、panel。
- color management、HDR、DSC、PSR。
- IGT KMS 测试。

推荐主线：

```text
vkms/simpledrm
    -> 真实驱动 KMS 目录
    -> atomic check/commit
    -> vblank/page flip event
    -> IGT kms_* 测试
```

建议源码搜索：

```bash
rg -n "atomic_check|atomic_commit|drm_crtc_handle_vblank|hotplug|connector" drivers/gpu/drm
```

适合输出：

- 一条 page flip 路径的完整解剖。
- 一个 IGT KMS 测试的源码与日志分析。
- 目标驱动 display 子系统地图。

### 3. 可选方向二：计算和命令提交

适合你如果更关心：

- command buffer。
- queue、ring、doorbell。
- scheduler、job、fence。
- GPU VM。
- hang/reset。
- Vulkan/compute 提交模型。

推荐主线：

```text
msm/panfrost submit
    -> amdgpu_cs_ioctl 或 xe exec
    -> scheduler run_job
    -> fence completion
    -> timeout/reset
```

建议源码搜索：

```bash
rg -n "submit|exec|drm_sched|run_job|timedout_job|dma_fence_signal" drivers/gpu/drm
```

适合输出：

- 一条 submit ioctl 的完整解剖。
- scheduler/fence 对象关系图。
- 一份 hang/reset 日志分析。

### 4. 可选方向三：移动 GPU

适合你如果有移动开发板，或对 SoC 图形栈感兴趣：

- `msm` / Adreno。
- `panfrost` / Mali。
- device tree。
- IOMMU/SMMU。
- runtime PM、devfreq、OPP。
- firmware、reset、thermal。

推荐主线：

```text
platform probe
    -> power/clock/reset
    -> GEM/BO
    -> GPU address space
    -> submit/job
    -> IRQ/fault/reset
```

适合输出：

- 一个移动 GPU 的 probe 到 submit 路径图。
- device tree resource 到驱动对象的对应表。
- power management 和 submit 的关系笔记。

### 5. 可选方向四：PC GPU

适合你如果有 AMD/Intel 真机，或目标是桌面 Linux 图形驱动：

- `amdgpu`。
- `i915` / `xe`。
- PCIe、BAR、firmware。
- VRAM/GTT/TTM。
- GPU VM。
- reset、RAS、debugfs。

推荐主线：

```text
PCI probe
    -> device init
    -> BO/VM
    -> command submission
    -> fence/IRQ
    -> reset/debugfs
```

适合输出：

- `amdgpu` BO/VM 深入笔记。
- `xe` 或 `i915` 模块结构图。
- 真机 debugfs 状态解读。

### 6. 可选方向五：Windows WDDM 映射

如果未来要看 Windows GPU 驱动，可以先把 Linux 里学到的概念做映射，而不是立刻跳进所有 WDDM 细节。

初步映射可以这样做：

```text
Linux DRM device       -> WDDM adapter/device 概念
GEM/BO/dma-buf         -> allocation / shared resource
GPU VM                 -> GPU virtual address management
DRM scheduler/fence    -> scheduler / monitored fence / sync object
KMS                    -> display miniport / VidPN 相关概念
ioctl                  -> DDI / user-kernel interface
```

这一方向的风险是资料体系和调试工具完全不同。建议先把 Linux 路线收束成 2 到 3 条扎实路径，再做术语迁移。

### 7. 选择方向的评分表

给每个方向打 1 到 5 分：

```text
兴趣强度：
硬件条件：
源码可读性：
可验证性：
职业相关度：
社区资料质量：
4 周内能否产出完整作品：
```

总分最高不一定必须选，但它会暴露一个现实问题：你想学的方向是否有足够环境支撑。

### 8. 下一阶段计划模板

建议写成这样：

```text
方向：
选择理由：
可用硬件：
不可用但需要的条件：
主线源码目录：
核心对象：
核心 ioctl 或路径：

Week 1：
目标：
源码入口：
实验/验证：
交付物：

Week 2：
目标：
源码入口：
实验/验证：
交付物：

Week 3：
目标：
源码入口：
实验/验证：
交付物：

Week 4：
目标：
源码入口：
实验/验证：
交付物：

最大风险：
替代方案：
```

每周交付物必须能被检查，例如路径图、函数链、运行日志、IGT 结果、debugfs 解读，而不是“阅读某目录”。

## 建议输出

- 专题计划
- 深挖阅读清单

## 完成标准

- 选定一个方向，而不是同时追所有方向。
- 写出至少 4 周的后续学习主题。
- 明确哪些 lab 需要真机、哪些可以源码阅读完成。

## 关联 Lab

- [Lab 23：选方向深挖](../../labs/lab-23-specialization/README.md)

## 下一步

进入 Session 24，复盘整套路线并把下一阶段计划固定下来。

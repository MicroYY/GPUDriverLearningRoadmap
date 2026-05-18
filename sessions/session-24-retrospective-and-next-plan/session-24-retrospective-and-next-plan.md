# Session 24：总结与下一阶段计划

## 目标

复盘这 24 个 session 的学习成果，确认已经建立的能力、仍然薄弱的主题，并形成下一阶段明确计划。

## 核心问题

- 我现在已经能独立看懂哪些驱动路径？
- 下一阶段应该继续补基础，还是深入某个驱动？
- 哪些输出可以证明这 24 周不是“看过”，而是真的建立了能力？

## 学习内容

### 1. 复盘不是列标题，而是证明能力

完成 24 个 session 后，最重要的问题不是“我看过哪些内容”，而是：

```text
我能不能拿到一个陌生 GPU 驱动目录，找到入口、对象、路径、同步和调试证据？
```

所以复盘要围绕能力，而不是围绕章节标题。

建议把每个能力都落到可验证证据：

- 能画图。
- 能追函数链。
- 能解释结构体关系。
- 能读日志。
- 能把用户态调用和内核对象对应起来。
- 能知道哪些结论只是推测，哪些有运行时证据。

### 2. 六个能力维度

#### 图形栈地图

你应该能解释：

```text
应用
  -> OpenGL/Vulkan/EGL/GBM
  -> Mesa
  -> libdrm
  -> ioctl/mmap
  -> DRM core
  -> 具体驱动
  -> GPU/display 硬件
```

检查问题：

- Mesa 和 `libdrm` 的职责差异是什么？
- render node 和 card node 的差异是什么？
- 用户态对象如何通过 handle/fd/id 引用内核对象？

#### 内核对象阅读

你应该能拆一个结构体：

```text
公共基类成员：
私有硬件状态：
链表/树/IDR 节点：
锁和引用计数：
ops/helper 回调：
生命周期入口：
```

看到 `container_of`、`list_head`、`ops`、`kref`、`dma_resv` 时，不应该再陌生。

#### DRM/KMS

你应该能讲清：

- connector、encoder、crtc、plane、framebuffer 的关系。
- atomic state、check、commit 的分工。
- page flip、vblank、event 的关系。
- `vkms` 和真实显示驱动的差异。

#### 显存管理

你应该能讲清：

- GEM、TTM、dma-buf 分别解决什么问题。
- BO 如何被 handle、fd、GPU VA、CPU mmap 引用。
- VRAM/GTT/system memory 的基本差异。
- eviction、migration、pin 为什么和 fence 有关。

#### 提交与同步

你应该能讲清：

- command buffer、queue、ring、doorbell 的区别。
- submit ioctl 如何走到 scheduler。
- job、entity、run_job、fence 的关系。
- IRQ 如何把硬件完成变成 fence signal。
- timeout 如何进入 reset。

#### 调试能力

你应该能使用或解释：

- `dmesg` 和 DRM debug。
- `/sys/kernel/debug/dri/`。
- trace/ftrace/trace-cmd。
- perf。
- IGT。
- 一份包含命令、日志、源码入口和结论的调试记录。

### 3. 做一次最终自测

选择下面任意三条路径，写成完整笔记：

```text
路径 A：用户态 DRM_IOCTL_VERSION 到 drm_version
路径 B：dumb buffer create -> mmap -> framebuffer
路径 C：atomic page flip -> vblank event
路径 D：GEM/BO create -> handle -> dma-buf export
路径 E：submit ioctl -> scheduler -> fence signal
路径 F：job timeout -> reset -> fence error
路径 G：probe -> drm_dev_register -> KMS objects
```

每条路径都要包含：

```text
用户态入口：
uapi 结构体：
内核入口：
关键对象：
锁/引用计数：
成功返回：
错误路径：
运行时证据：
还不确定的问题：
```

如果一条路径写不出来，它就是下一阶段的补课项。

### 4. 整理你的学习资产

建议把 24 周输出整理成下面目录或笔记结构：

```text
00-map/
  linux-graphics-stack.md
  drm-kms-object-model.md

01-code-reading/
  ioctl-template.md
  kernel-object-template.md
  driver-checklist.md

02-memory/
  gem-ttm-dmabuf.md
  amdgpu-bo-vm.md

03-submit-sync/
  scheduler-fence.md
  amdgpu-cs-path.md

04-display/
  atomic-page-flip.md
  vkms-simpledrm.md

05-debug/
  debugfs-trace-perf.md
  hang-reset-analysis.md
```

形式不重要，重要的是后面遇到问题能快速复用。

### 5. 下一阶段 8 周计划怎么写

计划要具体到每周交付物：

```text
Week 1：目标驱动目录地图
交付物：模块结构图 + 关键对象表

Week 2：一个创建路径
交付物：ioctl 到对象创建函数链

Week 3：一个映射或提交路径
交付物：BO/VM 或 submit/scheduler 图

Week 4：一个完成路径
交付物：IRQ/fence/vblank event 图

Week 5：一个异常路径
交付物：timeout/reset/fault 分析

Week 6：一个运行实验
交付物：命令、日志、trace/debugfs 记录

Week 7：对照测试或工具
交付物：IGT/perf/trace 分析

Week 8：总结
交付物：完整专题文档或小型分享稿
```

不要把计划写成“继续学习 amdgpu”。要写成“追 `amdgpu_cs_ioctl` 到 `run_job` 并画出 fence 生命周期”。

### 6. 最终复盘模板

```text
我已经能独立解释的 5 条路径：
1.
2.
3.
4.
5.

我已经完成的关键 lab：

我最常复用的源码入口：

我最可靠的调试工具：

我仍然薄弱的 5 个问题：
1.
2.
3.
4.
5.

下一阶段方向：

选择这个方向的理由：

需要补齐的环境或硬件：

下一阶段 8 周计划：

我希望 8 周后能交付的作品：
```

这份复盘写完，24 周学习才真正闭环。

## 建议输出

- 阶段总结
- 下一阶段 8 周计划

## 完成标准

- 写出一份阶段总结，而不是只列“学了哪些标题”。
- 选定下一阶段方向和每周可交付物。
- 明确需要补齐的环境、硬件、源码或工具条件。

## 关联 Lab

- [Lab 24：总结与下一阶段计划](../../labs/lab-24-retrospective-and-next-plan/lab-24-retrospective-and-next-plan.md)

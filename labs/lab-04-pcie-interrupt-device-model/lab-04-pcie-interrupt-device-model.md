# Lab 04：PCIe、中断与设备模型

## 对应 Session

- [Session 04：PCIe、中断与设备模型](../../sessions/session-04-pcie-interrupt-device-model/session-04-pcie-interrupt-device-model.md)

## 目标

理解一个 GPU 设备是如何被发现、绑定并处理中断的。

## 开始前先确认

- 已经完成 Session 04。
- 已经准备 Linux kernel 源码。
- 如果没有真实硬件，可以只做 `amdgpu`、`i915/xe`、`msm` 或 `panfrost` 的源码路径追踪。

## 任务

### 1. 找一个 DRM 驱动的 probe 入口

任选一个目标：

- PCIe 驱动：`amdgpu`、`i915`、`xe`
- platform 驱动：`msm`、`panfrost`

可以用：

```bash
rg -n "struct pci_driver|module_pci_driver|struct platform_driver|module_platform_driver|\\.probe" drivers/gpu/drm
```

记录它的 driver 结构体、probe 函数和注册入口。

### 2. 记录设备初始化路径

至少写出：

- 设备如何匹配到驱动。
- `drm_device` 在哪里创建或初始化。
- MMIO / BAR / platform resource 在哪里获取。
- DRM 设备在哪里注册到用户可见节点。

### 3. 找到 IRQ 注册和处理入口

记录：

- 调用 `request_irq` 或相关 helper 的位置。
- IRQ handler 名称。
- handler 里更新了什么状态，是否会 signal fence 或唤醒等待者。

### 4. 写一份初始化顺序表

按顺序记录：

```text
驱动注册入口：
设备匹配表：
probe：
资源获取：
MMIO / BAR / platform resource：
IRQ 注册：
drm_device 初始化：
drm_dev_register：
remove / error path：
```

## 交付物

- 设备初始化流程图
- 中断入口定位笔记
- 初始化顺序表

## 检查项

- [ ] 我找到一个 probe 入口。
- [ ] 我能区分 PCIe 和 platform 驱动入口形态。
- [ ] 我找到至少一个 IRQ 注册或处理函数。
- [ ] 我能指出 `drm_device` 是在哪一步进入 DRM core 的。

## 完成标准

- 你能从“设备出现”讲到“驱动注册 DRM device 并处理中断”的粗路径。

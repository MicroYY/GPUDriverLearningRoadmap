# Lab 14：阅读 `simpledrm`

## 对应 Session

- [Session 14：阅读 `simpledrm`](../../sessions/session-14-read-simpledrm/README.md)

## 目标

理解 `simpledrm` 的职责和初始化方式，并与 `vkms` 对比。

## 开始前先确认

- 已经完成 Session 14。
- 已经读过或完成 Lab 13，对 `vkms` 有基本印象。

## 任务

### 1. 找到 `simpledrm` 的设备注册路径

记录：

- platform driver 入口。
- framebuffer 信息来源。
- DRM device 创建和注册位置。

建议定位：

```bash
rg -n "simpledrm|simple_display_pipe|sysfb|aperture|platform_driver" drivers/gpu/drm drivers/firmware drivers/video
```

### 2. 记录 modeset 相关对象

至少找出：

- framebuffer
- simple display pipe
- connector
- mode
- format

### 3. 写一份和 `vkms` 的差异对比

比较：

- 是否虚拟显示。
- 是否依赖 firmware framebuffer。
- 是否模拟 composition。
- 适合学习哪些 DRM/KMS 概念。

### 4. 记录 firmware framebuffer 到 DRM 的交接

```text
firmware framebuffer 来源：
platform device：
framebuffer resource：
格式/尺寸/stride：
映射方式：
simple display pipe：
aperture handover：
被真实 GPU 驱动替换的位置：
```

## 交付物

- 对比笔记
- init 流程图
- firmware framebuffer 交接表

## 检查项

- [ ] 我找到 `simpledrm` 的初始化入口。
- [ ] 我能解释 firmware framebuffer 的角色。
- [ ] 我完成了和 `vkms` 的对比。
- [ ] 我能说清 `simpledrm` 的显示能力边界。

## 完成标准

- 你能解释为什么 `simpledrm` 能显示画面，但它不是完整 GPU 渲染驱动。

# 模块 3：Linux DRM/KMS 核心

## 目标

掌握 Linux GPU 驱动里最关键的公共框架和对象模型。

## 核心主题

- DRM/KMS 对象：`drm_device`、`connector`、`encoder`、`crtc`、`plane`、`framebuffer`。
- Atomic modesetting。
- GEM、TTM、`dma-buf`。
- `dma_fence`、`sync_file`、vblank、IRQ。

## 建议源码入口

- `drivers/gpu/drm/drm_ioctl.c`
- `drivers/gpu/drm/drm_atomic*`
- `drivers/gpu/drm/drm_gem*`
- `drivers/gpu/drm/drm_vblank.c`
- `include/drm/`

## 建议产出

- 一张对象关系图。
- 一篇显存管理对比笔记。
- 一篇 atomic modeset 流程笔记。

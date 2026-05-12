# Lab 20：Page flip 与显示输出

## 对应 Session

- [Session 20：Page flip 与显示输出](../../sessions/session-20-page-flip-and-display/README.md)

## 目标

理解 page flip、显示控制器和 vblank 的协作。

## 开始前先确认

- 已经完成 Session 20。
- 真机显示链路最完整；QEMU/vkms 可以完成通用 KMS 路径理解。

## 任务

### 1. 找一条 page flip 相关路径

可以从：

- atomic commit。
- plane state 更新。
- framebuffer 切换。
- vblank event。
- page flip event。

中选择一条主线。

建议定位：

```bash
rg -n "drm_mode_page_flip_ioctl|DRM_MODE_PAGE_FLIP_EVENT|drm_crtc_send_vblank_event|drm_atomic_commit|drm_framebuffer" drivers/gpu/drm include/uapi/drm
```

### 2. 记录显示输出涉及的对象

至少包含：

- crtc
- plane
- framebuffer
- connector
- mode
- vblank event
- atomic state

### 3. 画出 page flip 路径图

从用户态请求画到：

- atomic state。
- plane framebuffer 更新。
- commit。
- vblank。
- event 返回。

### 4. 区分渲染完成和显示完成

写一张对照表：

```text
渲染完成信号：
对应 fence：
page flip 请求：
新 framebuffer：
vblank / flip done：
用户态 event：
如果没有真机，哪些只能源码确认：
```

## 交付物

- page flip 路径图
- KMS / vblank 笔记
- 渲染完成 / 显示完成对照表

## 检查项

- [ ] 我能解释 page flip 的本质。
- [ ] 我找到 vblank 或 page flip event 相关入口。
- [ ] 我能说明 QEMU/vkms 和真机显示链路的观察差异。
- [ ] 我能解释 framebuffer 和 BO 不是同一个抽象层。

## 完成标准

- 你能把“画面切换”解释成 KMS 对象状态变化和显示时序协作。

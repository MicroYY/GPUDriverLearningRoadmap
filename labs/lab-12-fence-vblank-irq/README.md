# Lab 12：Fence、vblank、IRQ

## 对应 Session

- [Session 12：Fence、vblank、IRQ](../../sessions/session-12-fence-vblank-irq/README.md)

## 目标

理解同步、中断和显示刷新之间的关系。

## 开始前先确认

- 已经完成 Session 12。
- QEMU/vkms 可以完成通用路径理解；真实 GPU 可以提供更丰富的 IRQ 和 fence 日志。

## 任务

### 1. 跟踪一个 `dma_fence` 相关路径

记录：

- fence 创建位置。
- fence signal 位置。
- 等待或回调位置。
- 错误状态如何传播。

建议定位：

```bash
rg -n "dma_fence_init|dma_fence_signal|dma_fence_wait|dma_fence_set_error" drivers/gpu/drm drivers/dma-buf
```

### 2. 找到 vblank 相关核心函数

至少定位：

- vblank enable / disable。
- vblank event。
- page flip event。
- 和 KMS atomic commit 的关系。

可以用：

```bash
rg -n "drm_crtc_handle_vblank|drm_crtc_send_vblank_event|drm_send_event|vblank" drivers/gpu/drm
```

### 3. 总结中断、fence、page flip 的协作关系

画一张图，把下面几个点串起来：

- GPU 或显示硬件事件。
- IRQ handler。
- vblank / fence signal。
- 用户态等待或 event 返回。

### 4. 记录异步完成时间线

```text
提交点：
产生 fence 或 event：
硬件/虚拟事件：
IRQ/vblank 入口：
signal 或 send event：
用户态观察方式：
错误传播：
```

## 交付物

- 同步机制笔记
- 关系图
- 异步完成时间线

## 检查项

- [ ] 我能解释 `dma_fence` 表达什么。
- [ ] 我能解释 vblank 为什么和 page flip 强相关。
- [ ] 我能找到至少一个 signal 或 event 相关源码入口。
- [ ] 我能区分 render fence 完成和 page flip event 完成。

## 完成标准

- 你能讲清“异步完成”如何从硬件事件变成用户态可观察结果。

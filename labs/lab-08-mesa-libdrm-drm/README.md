# Lab 08：Mesa、libdrm、DRM 关系

## 对应 Session

- [Session 08：Mesa、libdrm、DRM 关系](../../sessions/session-08-mesa-libdrm-drm/README.md)

## 目标

明确用户态图形栈各层职责。

## 开始前先确认

- 已经完成 Session 08。
- 已经准备 Mesa、`libdrm` 和 Linux kernel 源码。

## 任务

### 1. 总结分层职责

至少覆盖：

- 应用 / API
- Mesa
- `libdrm`
- DRM core
- 具体内核驱动

### 2. 找一个 `libdrm` ioctl 封装函数

记录：

- 用户态函数名。
- ioctl 编号。
- 参数结构体。
- 内核端大致入口。

可以从 mode setting 或目标驱动私有 ioctl 包装开始。

建议先从这些命令定位：

```bash
rg -n "drmIoctl|drmModeAddFB2|drmModeAtomicCommit|DRM_IOCTL" libdrm
rg -n "DRM_IOCTL_MODE_ADDFB2|DRM_IOCTL_MODE_ATOMIC|drm_ioctl" drivers/gpu/drm include/uapi/drm
```

### 3. 画用户态与内核态分层图

图里标出：

- 用户态 / 内核态边界。
- `ioctl` / `mmap` 边界。
- 哪些对象只在用户态存在，哪些对象在内核态存在。

### 4. 写一张用户态/内核态对象对照表

```text
用户态资源：
用户态 handle / fd / id：
libdrm 函数：
uapi 结构体：
内核对象：
内核入口：
```

## 交付物

- 用户态图形栈总结
- 分层图
- 用户态/内核态对象对照表

## 检查项

- [ ] 我能解释 Mesa 和 `libdrm` 的区别。
- [ ] 我找到一个用户态 ioctl 包装。
- [ ] 我能把包装函数追到 DRM core 或驱动入口。
- [ ] 我能说明 handle、object id、dma-buf fd 各自适用的边界。

## 完成标准

- 你能说明为什么一个 GPU 问题有时必须同时看 Mesa、`libdrm` 和 kernel。

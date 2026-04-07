# Lab 05：`ioctl`、`mmap` 与驱动基础

## 对应 Session

- [Session 05：`ioctl`、`mmap` 与驱动基础](../../sessions/session-05-ioctl-mmap-driver-basics/README.md)

## 目标

建立用户态到内核态的基本调用链视角。

## 任务

1. 写一个最小 DRM 用户态程序，调用 `DRM_IOCTL_VERSION`。
2. 静态阅读 `drm_ioctl.c` 中对应路径。
3. 总结 `ioctl` 与 `mmap` 在驱动中的基本职责。

## 交付物

- 调用链笔记
- 关键函数列表

# Lab 22：完整读一次 `ioctl` 路径

## 对应 Session

- [Session 22：完整读一次 `ioctl` 路径](../../sessions/session-22-end-to-end-ioctl-path/README.md)

## 目标

完整解剖一个 ioctl 从用户态到驱动落点的全过程。

## 开始前先确认

- 已经完成 Session 22。
- 选择一个规模合适的 ioctl，避免第一次就选择最复杂的 command submission。

## 任务

### 1. 选一个具体 ioctl

推荐候选：

- `DRM_IOCTL_VERSION`
- dumb buffer create
- GEM close
- mode get resources
- 一个目标驱动的简单私有 ioctl

第一次建议选择 `DRM_IOCTL_VERSION` 或 dumb buffer create；如果选择 submit ioctl，要明确本周只追主干。

### 2. 跟踪用户态封装、DRM core 分发和驱动侧处理

记录：

- 用户态函数。
- ioctl 编号。
- 参数结构体。
- `drm_ioctl` 分发。
- 具体处理函数。
- 锁、引用计数、对象查找和错误返回。

建议定位：

```bash
rg -n "DRM_IOCTL_VERSION|DRM_IOCTL_MODE_CREATE_DUMB|drm_ioctl|DRM_IOCTL_DEF|DRM_IOCTL_DEF_DRV" drivers/gpu/drm include/uapi/drm include/drm libdrm
```

### 3. 记录关键对象和返回路径

输出一张路径表：

- 入口。
- 对象。
- 状态变化。
- 失败路径。
- 释放路径。

### 4. 写成可复用模板

```text
ioctl 名称：
用户态入口：
uapi 结构体：
file_operations：
DRM core 分发：
handler：
关键对象：
锁：
引用计数：
成功返回：
错误路径：
释放路径：
运行时证据：
```

## 交付物

- 路径解剖笔记
- 关键函数列表
- 可复用 ioctl 模板

## 检查项

- [ ] 我选定一个具体 ioctl。
- [ ] 我从用户态追到了内核处理函数。
- [ ] 我记录了关键对象和错误返回路径。
- [ ] 我能说明这条路径哪些属于用户态、DRM core、驱动私有实现。

## 完成标准

- 你能拿这份记录作为以后阅读任意 ioctl 的模板。

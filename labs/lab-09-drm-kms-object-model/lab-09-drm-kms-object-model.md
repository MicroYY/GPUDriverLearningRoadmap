# Lab 09：DRM/KMS 对象模型

## 对应 Session

- [Session 09：DRM/KMS 对象模型](../../sessions/session-09-drm-kms-object-model/session-09-drm-kms-object-model.md)

## 目标

把 connector、encoder、crtc、plane、fb 等对象关系讲清楚。

## 开始前先确认

- 已经完成 Session 09。
- 如果可以运行 `modetest`，优先用运行结果辅助理解；否则可以只做源码对象图。

## 任务

### 1. 观察或阅读 KMS 对象

任选一种方式：

- 运行 `modetest` 观察 connector、encoder、crtc、plane、fb。
- 阅读 `vkms` 或目标驱动的 KMS 对象初始化路径。

可选命令：

```bash
modetest -M vkms
modetest -M amdgpu
modetest -M i915
```

如果没有 `modetest`，用源码替代：

```bash
rg -n "drm_connector_init|drm_crtc_init|drm_universal_plane_init|drm_framebuffer" drivers/gpu/drm/vkms drivers/gpu/drm
```

### 2. 画出对象关系图

图里至少包含：

- `drm_device`
- connector
- encoder
- crtc
- plane
- framebuffer
- mode
- property

### 3. 解释一次 modeset 需要哪些对象协作

用自己的话描述：

- 输出接到哪里。
- 哪个 crtc 负责扫描。
- 哪个 plane 绑定哪个 framebuffer。
- property 如何表达状态。

### 4. 做一张对象 ID 到结构体的对照表

```text
用户态对象 id：
对象类型：
内核结构体：
初始化函数：
关键 property：
和其他对象的关系：
```

## 交付物

- 对象关系图
- KMS 对象说明
- 对象 ID / 结构体对照表

## 检查项

- [ ] 我能区分 connector、encoder、crtc、plane、framebuffer。
- [ ] 我能解释 property 在 KMS 状态里的作用。
- [ ] 我能说清一次 modeset 至少需要哪些对象。
- [ ] 我能把 `modetest` 输出或源码初始化函数映射到对象关系图里。

## 完成标准

- 你能看到一组 KMS 对象时，不再把它们当作孤立结构体，而能画出显示拓扑。

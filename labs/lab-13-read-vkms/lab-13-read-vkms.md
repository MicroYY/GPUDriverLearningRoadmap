# Lab 13：阅读 `vkms`

## 对应 Session

- [Session 13：阅读 `vkms`](../../sessions/session-13-read-vkms/session-13-read-vkms.md)

## 目标

从最简单的 DRM 驱动切入，理解驱动注册和最小对象集合。

## 开始前先确认

- 已经完成 Session 13。
- 推荐使用 QEMU 或原生 Linux 加载 `vkms`。
- 如果无法加载模块，也可以完成源码路径图。

## 任务

### 1. 找到 `vkms` 的 init / probe 路径

记录：

- 模块入口。
- platform device / driver 注册。
- probe 函数。
- `drm_device` 初始化和注册位置。

建议命令：

```bash
rg -n "module_|platform|probe|drm_dev_register|drm_mode_config" drivers/gpu/drm/vkms
```

### 2. 记录关键对象和回调

至少包含：

- connector
- encoder
- crtc
- plane
- composer
- vblank 或 CRC 相关逻辑
- `funcs` / helper callbacks

### 3. 画初始化流程图

从模块加载开始，画到用户态能看到 DRM/KMS 对象为止。

### 4. 如果环境允许，加载并观察 `vkms`

```bash
sudo modprobe vkms
modetest -M vkms
dmesg | tail -100
```

记录 `modetest` 里的 connector、crtc、plane，并把它们对应回源码初始化位置。

## 交付物

- `vkms` 结构总结
- init 流程图
- `modetest` 或源码对象对照表

## 检查项

- [ ] 我找到 `vkms` 的模块入口和 probe 路径。
- [ ] 我列出最小 KMS 对象集合。
- [ ] 我能说明 `vkms` 使用哪些 DRM helper。
- [ ] 我能说明 `vkms` 哪些行为是软件模拟而不是真实硬件。

## 完成标准

- 你能用 `vkms` 解释一个最小 KMS 驱动如何接入 DRM core。

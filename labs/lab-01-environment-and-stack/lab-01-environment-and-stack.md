# Lab 01：环境准备与图形栈总览

## 对应 Session

- [Session 01：环境准备与图形栈总览](../../sessions/session-01-environment-and-stack/session-01-environment-and-stack.md)

## 目标

把 Session 01 里讲到的“环境”和“整体地图”真正落到手上，形成后续可以复用的学习工作区和第一份交付物。

## 代码练习

### 1. 准备源码工作区

拉取后面会反复使用的源码：

```bash
mkdir -p ~/gpu-stack-study
cd ~/gpu-stack-study
git clone https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git
git clone https://gitlab.freedesktop.org/mesa/mesa.git
git clone https://gitlab.freedesktop.org/mesa/drm.git libdrm
```

### 2. 安装基础工具链

如果你使用 Ubuntu，可以直接安装：

```bash
sudo apt update
sudo apt install -y clangd ctags ripgrep gdb linux-tools-generic
```

### 3. 验证源码和搜索工具

执行下面几条命令，确认源码和基础搜索工具可用：

```bash
cd ~/gpu-stack-study
rg "drm_ioctl" linux/drivers/gpu/drm
rg "amdgpu_cs_ioctl" linux/drivers/gpu/drm
rg "drmMode" libdrm
```

### 4. 观察本机图形栈

```bash
ls -l /dev/dri/
lspci -k | grep -A3 -E "VGA|3D|Display"
lsmod | grep -E "amdgpu|i915|xe|nouveau|msm|panfrost|vkms|drm"
```

如果安装了 Mesa / Vulkan 工具，也记录：

```bash
glxinfo -B
vulkaninfo --summary
```

如果某些命令不存在，不需要在这一节卡住，先继续往下做。

### 5. 画第一张总览图

用自己的方式画一张从应用到硬件的路径图，至少包含：

- 应用 / API
- Mesa
- `libdrm`
- `/dev/dri/card*` 或 `/dev/dri/renderD*`
- DRM/KMS core
- 具体驱动
- GPU 或显示硬件

这张图会在后面反复修正，不要求第一次就完美。

## 概念解释

### 1. 解释 `/dev/dri/` 里的节点

用自己的话解释下面两个节点的区别：

- `/dev/dri/card*`
- `/dev/dri/renderD*`

解释时至少回答：

- 哪一个更接近显示控制
- 哪一个更接近渲染或计算提交
- 它们和用户态程序访问 GPU 有什么关系

### 2. 解释当前机器正在使用的驱动

根据 `lspci -k` 和 `lsmod` 的输出，回答：

- 当前机器上有哪些显示或 GPU 设备
- 这些设备绑定了哪个内核驱动
- 当前加载了哪些 DRM / GPU 相关模块

### 3. 解释三份源码分别对应哪一层

结合 Session 01 的图形栈总览，解释下面三个目录分别对应哪一层：

- `mesa`
- `libdrm`
- `linux/drivers/gpu/drm`

### 4. 解释用户态工具看到的信息

如果你运行了 `glxinfo -B` 或 `vulkaninfo --summary`，用自己的话说明：

- 用户态图形栈识别到了哪个 GPU
- 输出里出现了哪些 Mesa / Vulkan / driver 信息
- 这些信息和 `/dev/dri/`、内核模块之间有什么对应关系

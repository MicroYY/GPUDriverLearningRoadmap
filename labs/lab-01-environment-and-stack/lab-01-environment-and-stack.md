# Lab 01：环境准备与图形栈总览

## 对应 Session

- [Session 01：环境准备与图形栈总览](../../sessions/session-01-environment-and-stack/session-01-environment-and-stack.md)

## 目标

把 Session 01 里讲到的“环境”和“整体地图”真正落到手上，形成后续可以复用的学习工作区和第一份交付物。

## 开始前先决定

- 你的主学习环境是什么
  建议参考 [docs/roadmap.md](../../docs/roadmap.md) 里的环境建议和适配范围。
- 你这一阶段是只做源码阅读，还是还要一起做实验
- 你的源码和笔记准备放在哪个固定工作区

## 任务

### 1. 确认主学习环境

优先考虑：

- 原生 Linux 测试机
- QEMU Linux 虚拟机

如果你当前只打算先完成前几节的源码阅读，也可以先用现有环境开始，但要明确后面是否补完整 Linux 实验环境。

### 2. 准备源码工作区

至少准备下面三个源码：

- Linux kernel
- Mesa
- `libdrm`

可以直接执行：

```bash
mkdir -p ~/gpu-stack-study
cd ~/gpu-stack-study
git clone https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git
git clone https://gitlab.freedesktop.org/mesa/mesa.git
git clone https://gitlab.freedesktop.org/mesa/drm.git libdrm
```

### 3. 安装基础工具链

至少准备下面这些工具：

- `clangd`
- `ctags`
- `ripgrep`
- `gdb`
- `perf`

如果你使用 Ubuntu，可以直接执行：

```bash
sudo apt update
sudo apt install -y clangd ctags ripgrep gdb linux-tools-generic
```

安装完成后，至少确认后面可以用它们做搜索、跳转、调试和观察。

### 4. 观察本机图形栈

如果当前环境是 Linux，记录下面几组命令输出：

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

如果命令不存在，不需要卡住；在记录里写清楚缺少哪个工具，以及后面是否需要补装。

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

## 交付物

- 环境记录
- 图形栈总览图
- 源码工作区路径
- 已安装工具清单

## 检查项

- [ ] 已经确定主学习环境
- [ ] 已经准备 Linux kernel 源码
- [ ] 已经准备 Mesa 源码
- [ ] 已经准备 `libdrm` 源码
- [ ] 已经安装 `clangd`
- [ ] 已经安装 `ctags`
- [ ] 已经安装 `ripgrep`
- [ ] 已经安装 `gdb`
- [ ] 已经安装 `perf`
- [ ] 已经记录 `/dev/dri/` 或说明当前环境为什么没有
- [ ] 已经画出第一张图形栈总览图

## 完成标准

- 你能在自己的机器或虚拟机上指出用户态源码、内核源码、DRM 设备节点和当前 GPU/DRM 模块分别在哪里。

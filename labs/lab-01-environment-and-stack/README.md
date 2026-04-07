# Lab 01：环境准备与图形栈总览

## 对应 Session

- [Session 01：环境准备与图形栈总览](../../sessions/session-01-environment-and-stack/README.md)

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
- [ ] 已经完成图形栈总览图
- [ ] 已经完成环境说明文档

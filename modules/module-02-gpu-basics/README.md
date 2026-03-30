# 模块 2：GPU 与图形基础

## 目标

理解 GPU 的执行模型，以及图形 API、用户态驱动和内核驱动之间的关系。

## 对应 roadmap 周次

- 第 6 到 8 周

## 对应实验

- 当前没有独立 lab，建议本模块以图示、路径梳理和概念笔记为主。

## 核心主题

- 图形流水线和计算流水线。
- OpenGL、Vulkan、EGL、GBM、DRM 的基本职责。
- `command buffer`、`ring buffer`、`queue`、`doorbell`。
- VRAM、GTT、system memory、BAR 映射。

## 建议产出

- 一篇 “GPU 执行模型速记”。
- 一张 “应用 -> Mesa -> libdrm -> kernel driver -> GPU” 数据路径图。

## 下一步

学完这一模块后进入 DRM/KMS 核心模块，开始从框架角度理解 Linux GPU 驱动。

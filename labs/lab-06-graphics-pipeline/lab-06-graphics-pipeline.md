# Lab 06：GPU 图形流水线

## 对应 Session

- [Session 06：GPU 图形流水线](../../sessions/session-06-graphics-pipeline/session-06-graphics-pipeline.md)

## 目标

用自己的图和文字讲清图形流水线各阶段。

## 开始前先确认

- 已经完成 Session 06。
- 这个 lab 以图解和概念映射为主，不要求真实 GPU 环境。

## 任务

### 1. 画出顶点到输出的流水线

至少包含：

- vertex input
- vertex shader
- primitive assembly
- rasterization
- fragment / pixel shader
- output merge
- framebuffer

### 2. 标注每个阶段的输入输出

对每个阶段写一句：

- 输入是什么。
- 输出是什么。
- 它更偏 API / shader / 硬件固定功能 / 驱动资源管理中的哪一类。

### 3. 标出驱动最直接参与的地方

重点标注：

- buffer 和 texture 资源管理。
- pipeline state 和 shader 编译结果。
- command buffer 构建和提交。
- framebuffer、page flip 和同步。

### 4. 把一次 draw 拆成驱动对象

用下面模板写一张映射表：

```text
create vertex buffer -> 
compile shader ->
create texture ->
create framebuffer ->
record command buffer ->
submit ->
wait fence ->
page flip ->
```

每一行都写出它可能对应的用户态对象、内核对象或源码方向。比如 `submit` 对应 `ioctl`、scheduler、ring、fence。

## 交付物

- 图形流水线图
- 阶段说明笔记
- draw 到驱动对象的映射表

## 检查项

- [ ] 我能按顺序讲出图形流水线主要阶段。
- [ ] 我能指出哪些状态通常由用户态驱动组织。
- [ ] 我能把最终 framebuffer 和 DRM/KMS 显示路径联系起来。
- [ ] 我能区分“渲染完成”和“显示出来”不是同一个完成点。

## 完成标准

- 你能解释“一帧图像”不是直接从应用跳到屏幕，而是经过资源、命令、同步和显示链路。

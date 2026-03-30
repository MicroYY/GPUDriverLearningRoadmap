# 模块 4：真实驱动源码阅读

## 目标

从公共框架过渡到具体驱动实现，形成稳定的源码阅读方法。

## 对应 roadmap 周次

- 第 13 到 18 周

## 对应实验

- [Lab 2：跟踪一次 `ioctl` 调用路径](../../labs/lab-02-ioctl-tracing/README.md)
- [Lab 3：阅读一个 buffer object 的生命周期](../../labs/lab-03-bo-lifecycle/README.md)

## 建议顺序

1. `vkms`
2. `simpledrm`
3. `msm` 或 `panfrost`
4. `i915` 或 `xe`
5. `amdgpu`

## 阅读时重点回答

- 驱动如何注册进入 DRM 框架？
- buffer object 如何创建、映射和释放？
- 命令如何提交到硬件？
- fence 和中断如何协同工作？
- reset 和错误恢复从哪里开始看？

## 建议产出

- 每个驱动一份结构总结。
- 每个驱动一张 “初始化 -> 提交 -> 完成” 流程图。

## 配套 lab

- [Lab 2：跟踪一次 `ioctl` 调用路径](../../labs/lab-02-ioctl-tracing/README.md)
- [Lab 3：阅读一个 buffer object 的生命周期](../../labs/lab-03-bo-lifecycle/README.md)

# Lab 11：GEM、TTM、dma-buf

## 对应 Session

- [Session 11：GEM、TTM、dma-buf](../../sessions/session-11-gem-ttm-dma-buf/session-11-gem-ttm-dma-buf.md)

## 目标

比较三种核心对象 / 机制在驱动中的职责差异。

## 开始前先确认

- 已经完成 Session 11。
- 当前 lab 可以只做源码阅读，不要求真实 GPU。

## 任务

### 1. 阅读一条 GEM helper 路径

建议从这些入口选择：

- dumb buffer 创建。
- GEM object 初始化。
- GEM mmap。
- PRIME / dma-buf 导出。

定位命令：

```bash
rg -n "dumb_create|drm_gem_handle_create|drm_gem_mmap|prime_handle_to_fd|dma_buf_export" drivers/gpu/drm drivers/dma-buf include/drm
```

### 2. 找一个使用 TTM 的驱动入口

推荐看：

- `amdgpu`
- `radeon`
- `nouveau`

记录它如何把 GEM object、TTM BO 和驱动私有 BO 关联起来。

### 3. 总结 `dma-buf` 的导出 / 导入思路

回答：

- 为什么要用 fd 表示共享 buffer。
- exporter 和 importer 各自负责什么。
- fence / reservation object 在共享里有什么意义。

### 4. 写一张 BO 多重身份表

```text
驱动私有 BO：
GEM object：
TTM object：
GEM handle：
mmap offset：
dma-buf fd：
reservation / fence：
释放路径：
```

## 交付物

- GEM / TTM / dma-buf 对比表
- BO 多重身份表

## 检查项

- [ ] 我能解释 GEM 的作用。
- [ ] 我能解释 TTM 相比普通 GEM helper 多解决什么问题。
- [ ] 我能说明 `dma-buf` 为什么适合跨设备共享。
- [ ] 我能说清一个 BO 被用户态、内核态和其他设备分别如何引用。

## 完成标准

- 你能把一个 buffer object 放进“对象、内存域、映射、共享、同步”这几个维度里理解。

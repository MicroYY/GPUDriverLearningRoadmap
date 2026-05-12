# Lab 16：阅读 `i915` 或 `xe`

## 对应 Session

- [Session 16：阅读 `i915` 或 `xe`](../../sessions/session-16-read-i915-or-xe/README.md)

## 目标

理解复杂 PC GPU 驱动的模块边界和核心对象。

## 开始前先确认

- 已经完成 Session 16。
- 在 `i915` 和 `xe` 中选择一个作为主线。
- 如果没有 Intel GPU 真机，可以先完成源码地图和对象生命周期追踪。

## 任务

### 1. 列出主要子目录和职责

不要一上来追所有调用链。先整理：

- driver / device 初始化。
- GEM / BO。
- VM / address space。
- GT / engine / ring。
- display。
- scheduler / submit。

建议命令：

```bash
find drivers/gpu/drm/i915 -maxdepth 2 -type d | sort
find drivers/gpu/drm/xe -maxdepth 2 -type d | sort
rg -n "struct drm_i915_private|struct xe_device|struct xe_bo|struct xe_vm|exec|gem_create" drivers/gpu/drm/i915 drivers/gpu/drm/xe
```

### 2. 找一个 BO / VM / file private 入口

任选一条：

- BO 创建。
- VM 创建或绑定。
- file private 初始化。
- GEM handle 创建。

记录结构体、初始化函数、释放函数和引用关系。

### 3. 总结推荐阅读顺序

写出你自己的下一步阅读顺序，不少于 5 个入口。

### 4. 写一张大型驱动地图

```text
选择驱动：
核心 device 结构：
BO 结构：
VM 结构：
file private：
submit / exec 入口：
engine / GT：
display 子系统：
debugfs / trace：
本周暂时跳过的复杂分支：
```

## 交付物

- 模块结构总结
- 阅读入口清单
- 大型驱动地图

## 检查项

- [ ] 我选定了 `i915` 或 `xe`。
- [ ] 我完成了子目录职责表。
- [ ] 我追踪了至少一个 BO / VM / file private 入口。
- [ ] 我明确了下一周继续追哪一条主线，而不是同时追所有模块。

## 完成标准

- 你能把复杂驱动先拆成模块地图，而不是被单个函数调用链拖走。

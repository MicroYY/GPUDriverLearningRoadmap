# Lab 17：阅读 `amdgpu` 显存管理

## 对应 Session

- [Session 17：阅读 `amdgpu` 显存管理](../../sessions/session-17-read-amdgpu-memory/README.md)

## 目标

理解 `amdgpu` 的 VM、BO、迁移和回收路径。

## 开始前先确认

- 已经完成 Session 17。
- 没有 AMD GPU 真机也可以完成源码阅读；运行时 debugfs 和日志观察需要真实环境。

## 任务

### 1. 找到 VM 和 BO 核心结构体

至少记录：

- `amdgpu_bo`
- `amdgpu_vm`
- TTM BO 相关成员
- GEM object 相关成员

建议命令：

```bash
rg -n "struct amdgpu_bo|struct amdgpu_vm|amdgpu_bo_create|amdgpu_vm_bo|ttm_buffer_object" drivers/gpu/drm/amd/amdgpu drivers/gpu/drm/ttm
```

### 2. 找到迁移 / shrinker 相关入口

记录：

- BO placement。
- pin / unpin。
- eviction。
- shrinker。
- VM bind / map。

可以继续定位：

```bash
rg -n "placement|pin|unpin|evict|shrinker|validate|amdgpu_vm_update|amdgpu_vm_bo_update" drivers/gpu/drm/amd/amdgpu
```

### 3. 画出显存管理路径图

图里至少包含：

- 用户态创建 buffer。
- GEM/BO 创建。
- TTM placement。
- VRAM/GTT/system memory。
- GPU VM 映射。
- 回收或迁移路径。

### 4. 写一张 BO/VM 生命周期表

```text
创建 ioctl：
amdgpu_bo 创建：
GEM handle：
TTM placement：
CPU mmap / vmap：
GPU VM bind：
页表更新：
eviction / migration：
debugfs 可观察节点：
释放路径：
```

## 交付物

- VM / BO 笔记
- 显存管理路径图
- BO/VM 生命周期表

## 检查项

- [ ] 我能解释 `amdgpu_bo`、GEM object、TTM BO 的关系。
- [ ] 我找到 BO 创建和 VM 映射入口。
- [ ] 我能解释迁移或 eviction 为什么会发生。
- [ ] 我能区分 VRAM、GTT、system memory 和 visible VRAM 的角色。

## 完成标准

- 你能把 `amdgpu` 显存管理看成对象、内存域和地址空间三件事的组合。

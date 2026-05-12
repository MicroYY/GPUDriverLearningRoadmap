# Lab 18：阅读 `amdgpu` 命令提交和调度

## 对应 Session

- [Session 18：阅读 `amdgpu` 命令提交和调度](../../sessions/session-18-read-amdgpu-submission/README.md)

## 目标

理解调度、提交、fence 和完成回收路径。

## 开始前先确认

- 已经完成 Session 18。
- 建议先完成 Lab 17，否则 BO list、VM 和 fence 的关系会比较难接上。

## 任务

### 1. 找到命令提交入口

记录：

- `amdgpu_cs_ioctl` 或相关入口。
- 参数解析。
- BO list 处理。
- IB / job 创建。
- 依赖和同步处理。

建议命令：

```bash
rg -n "amdgpu_cs_ioctl|amdgpu_cs_parser|amdgpu_cs_submit|amdgpu_job|amdgpu_job_run|amdgpu_fence" drivers/gpu/drm/amd/amdgpu drivers/gpu/drm/scheduler
```

### 2. 记录 scheduler / fence 主要对象

至少包含：

- job
- entity
- scheduler
- ring
- fence
- completion / IRQ 相关入口

### 3. 画出提交到完成的路径图

从用户态 ioctl 画到：

- job 入队。
- scheduler 选择。
- ring 提交。
- fence signal。
- 资源释放或错误返回。

### 4. 写一张 cs ioctl 解剖表

```text
ioctl 入口：
parser 结构：
chunk 类型：
BO list：
IB：
依赖 fence：
job：
scheduler entity：
run_job：
ring submit：
fence signal：
timeout：
释放路径：
```

## 交付物

- scheduler / fence 笔记
- 命令提交流程图
- cs ioctl 解剖表

## 检查项

- [ ] 我找到 `amdgpu` 命令提交入口。
- [ ] 我能解释 job、ring、scheduler、fence 的关系。
- [ ] 我画出了从提交到完成的路径。
- [ ] 我能指出 timeout 或错误传播会从哪里进入后续恢复路径。

## 完成标准

- 你能把“提交命令”拆成参数校验、对象准备、调度、硬件执行和完成通知。

# Lab 21：Trace、debugfs、perf

## 对应 Session

- [Session 21：Trace、debugfs、perf](../../sessions/session-21-trace-debugfs-perf/session-21-trace-debugfs-perf.md)

## 目标

掌握常见 GPU 驱动调试工具的基础用法。

## 开始前先确认

- 已经完成 Session 21。
- 推荐使用原生 Linux 或 QEMU。真实 GPU 能提供更多驱动私有 debugfs 节点。

## 任务

### 1. 找到一个 driver 相关 debugfs 入口

记录：

- 节点路径。
- 节点输出含义。
- 对应源码实现。

如果没有真实 GPU，可以从 DRM 通用 debugfs 或 `vkms` 相关节点开始。

可用命令：

```bash
sudo mount -t debugfs none /sys/kernel/debug
find /sys/kernel/debug/dri -maxdepth 2 -type f | sort
rg -n "debugfs|seq_file|drm_debugfs" drivers/gpu/drm
```

### 2. 运行一次 trace / perf 观察

任选一种：

- ftrace。
- trace-cmd。
- perf。
- DRM debug log。
- `dmesg` 加动态 debug。

记录命令、输出和环境。

示例命令：

```bash
sudo trace-cmd list | grep -E "drm|dma_fence|gpu|sched"
sudo perf top -g
sudo sh -c 'echo 0x1ff > /sys/module/drm/parameters/debug'
```

### 3. 把日志和源码路径对应起来

至少给出：

- 看到的事件。
- 事件对应的源码文件或函数。
- 你从这次观察得出的结论。

### 4. 固定一份调试记录格式

```text
问题：
环境：
命令：
debugfs 输出：
trace/perf/dmesg 输出：
对应源码：
确认的结论：
仍需验证：
```

## 交付物

- 调试记录
- 工具速查表
- debugfs/trace/perf 证据表

## 检查项

- [ ] 我记录了至少一个 debugfs 节点。
- [ ] 我运行或静态分析了一种 trace/perf/log 工具。
- [ ] 我把输出对应到了源码入口。
- [ ] 我的调试记录包含命令、环境、输出和结论。

## 完成标准

- 你能写出一份别人可以复现的 GPU 驱动调试记录。

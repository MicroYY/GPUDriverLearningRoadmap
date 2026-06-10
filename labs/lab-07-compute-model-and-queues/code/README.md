# Lab 07 代码实验

这个目录提供一个最小用户态 C 代码实验，用来模拟 GPU 提交路径里常见的 `ops table` 设计：

- 同一个 queue 对象绑定不同 `ops`
- FIFO / LIFO 两种提交策略
- pending / completed 状态流转
- 通过测试验证回调表分发行为

这部分从 Lab 02 拆出来，放在队列主题下展开。Lab 02 只要求理解 `container_of` 和侵入式链表；Lab 07 再练“队列对象 + 行为表”。

## 学生任务

补齐下面文件里的 `TODO(student)`：

- `include/queue_ops.h`
- `src/queue_ops.c`

测试代码在：

- `tests/test_queue_ops.c`

## Windows 运行测试

先安装一个 C 编译器：

- Visual Studio Build Tools C/C++ 工具链
- LLVM/Clang
- MinGW-w64 GCC

然后在 PowerShell 里运行：

```powershell
powershell -ExecutionPolicy Bypass -File .\run-tests.ps1
```

清理生成文件：

```powershell
powershell -ExecutionPolicy Bypass -File .\run-tests.ps1 -Clean
```

## Linux / WSL 运行测试

```bash
make test
```

清理生成文件：

```bash
make clean
```

初始代码预期会测试失败。每补完一组 TODO，测试会继续往后推进，直到全部通过。

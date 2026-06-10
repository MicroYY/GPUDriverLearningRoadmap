# Lab 02 代码实验

这个目录提供一个最小用户态 C 代码实验，用来模拟 Linux 内核里几种高频结构设计：

- 侵入式双向链表
- `container_of`
- 对象状态流转

`ops` table 只在本节讲义中先建立概念，完整代码练习放到后续 `file_operations`、DRM/KMS 回调表和 scheduler 相关章节。

## 学生任务

补齐下面文件里的 `TODO(student)`：

- `include/lab02_list.h`
- `src/lab02_list.c`
- `src/job_queue.c`

测试代码在：

- `tests/test_lab02.c`

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

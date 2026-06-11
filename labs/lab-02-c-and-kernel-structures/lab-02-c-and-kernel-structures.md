# Lab 02：C 与内核数据结构

## 代码实验

本 lab 要完成 3 个小实验：

- `container_of`：从成员指针找回外层对象。
- 侵入式双向链表：实现 `list_head` 的初始化、插入、删除。
- `job_queue`：用链表模拟 job 从 pending 到 done 的状态流转。

实现顺序：

1. 实现 `container_of`
2. 实现 `list_init` / `list_empty`
3. 实现 `list_add` / `list_add_tail` / `list_del`
4. 实现 `job_queue_init`
5. 实现 `job_queue_submit` / `job_queue_complete_next`
6. 实现 pending/done 计数

## 代码位置

代码目录：

- [code](code/)

需要补充实现的文件：

- [lab02_list.h](code/include/lab02_list.h)
- [lab02_list.c](code/src/lab02_list.c)
- [job_queue.c](code/src/job_queue.c)

测试入口：

- [test_lab02.c](code/tests/test_lab02.c)

## 运行测试

在 Windows PowerShell 里运行：

```powershell
cd labs\lab-02-c-and-kernel-structures\code
powershell -ExecutionPolicy Bypass -File .\run-tests.ps1
```

清理生成文件：

```powershell
powershell -ExecutionPolicy Bypass -File .\run-tests.ps1 -Clean
```

在 Linux / WSL 里运行：

```bash
cd labs/lab-02-c-and-kernel-structures/code
make test
```

清理生成文件：

```bash
make clean
```

Windows 版本会自动寻找 `cl.exe`、`clang` 或 `gcc`。如果本机没有 C 编译器，需要先安装 Visual Studio Build Tools、LLVM/Clang 或 MinGW-w64。

测试会按小实验打印 `RUN` / `PASS` / `FAIL`，方便你看到当前通过到了哪一块。初始代码里保留了 `TODO(student)`，所以第一次运行测试失败是正常的。

## 对应 Session

- [Session 02：C 与内核数据结构](../../sessions/session-02-c-and-kernel-structures/session-02-c-and-kernel-structures.md)

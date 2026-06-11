# Lab 02：C 与内核数据结构

## 代码实验

本 lab 要完成 3 个小实验：

### 1. `container_of`

从成员指针找回外层对象。

相关代码：

- [lab02_list.h](code/include/lab02_list.h)：`struct list_head`、`container_of`、`list_entry`
- [test_lab02.c](code/tests/test_lab02.c)：`test_container_of`

需要实现：

- `container_of`

### 2. 侵入式双向链表

实现 `list_head` 的初始化、判空、头插、尾插和删除。

相关代码：

- [lab02_list.h](code/include/lab02_list.h)：`struct list_head` 只有 `next` / `prev`
- [lab02_list.c](code/src/lab02_list.c)：链表函数的 TODO
- [test_lab02.c](code/tests/test_lab02.c)：`test_list_init_and_empty`、`test_list_add_head_order`、`test_list_add_tail_and_delete`

这个实验使用环形双向链表。空链表时，`head->next` 和 `head->prev` 都指向 `head` 自己。

需要实现：

- `list_init`
- `list_empty`
- `list_add`
- `list_add_tail`
- `list_del`

### 3. `job_queue`

用链表模拟 job 从 pending 到 done 的状态流转。

相关代码：

- [job_queue.h](code/include/job_queue.h)：`enum job_state`、`struct job`、`struct job_queue`
- [job_queue.c](code/src/job_queue.c)：`job_init` 已经实现，其余函数留给实验
- [test_lab02.c](code/tests/test_lab02.c)：`test_job_queue_init`、`test_job_queue_submit`、`test_job_queue_complete_next`

`struct job` 内嵌一个 `struct list_head link`。`struct job_queue` 里有两条链表：`pending` 保存等待完成的 job，`done` 保存已经完成的 job。

需要实现：

- `job_queue_init`
- `job_queue_submit`
- `job_queue_complete_next`
- pending/done 计数

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

Windows 版本会自动寻找 `cl.exe`、`clang` 或 `gcc`。MSVC 使用 `/std:clatest`，GCC/Clang 使用 `-std=c2x`。如果本机没有 C 编译器，需要先安装 Visual Studio Build Tools、LLVM/Clang 或 MinGW-w64。

测试会按小实验打印 `[PASS]` / `[FAIL]` / `[SKIP]`，方便你看到当前通过到了哪一块。初始代码里保留了 `TODO(student)`，所以第一次运行测试失败是正常的。

## 对应 Session

- [Session 02：C 与内核数据结构](../../sessions/session-02-c-and-kernel-structures/session-02-c-and-kernel-structures.md)

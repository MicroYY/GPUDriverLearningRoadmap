# Lab 05：`ioctl`、`mmap` 与驱动基础

## 对应 Session

- [Session 05：`ioctl`、`mmap` 与驱动基础](../../sessions/session-05-ioctl-mmap-driver-basics/README.md)

## 目标

建立用户态到内核态的基本调用链视角。

## 开始前先确认

- 已经完成 Session 05。
- 当前环境最好能访问 `/dev/dri/*`。如果不能，也可以先做静态源码追踪。

## 任务

### 1. 写或阅读一个最小 DRM 用户态程序

目标是调用 `DRM_IOCTL_VERSION`，记录：

- 打开的设备节点。
- 传入的 ioctl 编号。
- 参数结构体。
- 返回值和错误码。

可以参考这个最小形态：

```c
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <xf86drm.h>

int main(void)
{
    int fd = open("/dev/dri/renderD128", O_RDWR | O_CLOEXEC);
    struct drm_version ver = {0};
    char name[128] = {0};

    if (fd < 0)
        return 1;

    ver.name = name;
    ver.name_len = sizeof(name);

    if (ioctl(fd, DRM_IOCTL_VERSION, &ver) == 0)
        printf("%s\n", name);

    close(fd);
    return 0;
}
```

如果不能编译运行，就把这段作为静态阅读样例。

### 2. 静态阅读 `drm_ioctl.c`

追踪：

- `drm_ioctl`
- ioctl 表查找。
- 权限和 feature 检查。
- 具体处理函数。

建议定位命令：

```bash
rg -n "DRM_IOCTL_VERSION|drm_version|drm_ioctl|DRM_IOCTL_DEF" drivers/gpu/drm include/uapi/drm include/drm
```

### 3. 补一条 `mmap` 路径的静态阅读

不要求本周完全吃透 GEM mmap，但至少写清：

- `mmap` 和 `ioctl` 解决的问题有什么不同。
- 为什么 buffer object 经常需要映射到用户态。
- fake offset 或 GEM mmap 大概在哪里出现。

### 4. 记录一次 ioctl 解剖表

```text
用户态函数：
ioctl 宏：
uapi 结构体：
file_operations 入口：
DRM core 分发函数：
handler：
权限 flag：
返回字段：
错误码：
```

## 交付物

- 调用链笔记
- 关键函数列表
- ioctl 解剖表

## 检查项

- [ ] 我能从用户态 ioctl 编号追到内核处理函数。
- [ ] 我知道 DRM core 和驱动私有 ioctl 表的区别。
- [ ] 我能解释 `mmap` 在图形驱动里的基本作用。
- [ ] 我能说清 handle、fd、内核对象指针不是同一件事。

## 完成标准

- 你能画出一次简单 ioctl 从用户态到 DRM core 的路径。

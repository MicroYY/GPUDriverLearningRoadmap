# Session 22：完整读一次 `ioctl` 路径

## 目标

把前面的分散理解收拢成一次从用户态到驱动的完整路径解剖，形成一份可以复用的源码阅读样板。

## 核心问题

- 一个典型 ioctl 的完整调用链是什么？
- 哪些对象会在这条路径中被创建、引用和释放？
- 这条路径里哪些环节属于用户态、DRM core、驱动私有实现和硬件交互？

## 学习内容

### 1. 为什么要完整读一次 ioctl

前面每节都在学局部：对象、地址空间、提交、fence、KMS、debugfs。Session 22 要把它们收束成一次完整路径。

你要能从用户态的一行调用讲到内核里的对象变化：

```text
用户态函数
    -> ioctl 宏和 uapi 结构体
    -> 系统调用和 file_operations
    -> drm_ioctl 分发
    -> DRM core 或驱动私有 handler
    -> 对象查找 / 创建 / 引用
    -> 锁和权限检查
    -> 成功返回或 error path 清理
```

这是一种可以复用到任何驱动的源码阅读样板。

### 2. 选择一个合适的 ioctl

不要第一次就选最复杂的 submit。推荐顺序：

1. `DRM_IOCTL_VERSION`
   最适合理解 DRM core ioctl 分发。

2. dumb buffer create/map
   适合理解 KMS、GEM handle、mmap offset。

3. GEM create
   适合理解驱动私有 BO 创建。

4. submit ioctl
   适合理解 BO list、VM、scheduler、fence，但复杂度高。

选择标准很简单：一周内能画完整路径，而不是只追到一半。

### 3. 用户态起点

先写一个最小用户态程序或找到 `libdrm` 包装。

例如 `DRM_IOCTL_VERSION`：

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

    ver.name = name;
    ver.name_len = sizeof(name);

    if (ioctl(fd, DRM_IOCTL_VERSION, &ver) == 0)
        printf("driver: %s\n", name);

    close(fd);
    return 0;
}
```

如果环境没有 render node，可以改用 `/dev/dri/card0`。真正学习重点不是程序本身，而是这个 ioctl 进入内核后的路径。

### 4. 内核分发路径

追踪时按下面顺序：

```bash
rg -n "DRM_IOCTL_VERSION|drm_version|drm_ioctl|DRM_IOCTL_DEF" drivers/gpu/drm include/uapi/drm include/drm
```

记录：

```text
ioctl 宏：
uapi 参数结构体：
file_operations 入口：
drm_ioctl：
ioctl descriptor：
handler 函数：
权限 flag：
返回数据写入位置：
```

如果是驱动私有 ioctl，还要继续找：

```text
驱动 drm_driver.ioctls：
DRM_IOCTL_DEF_DRV 表项：
驱动 handler：
file->driver_priv：
dev 私有结构：
```

### 5. 对象、锁、引用计数和错误路径

完整路径不能只写成功流程，还要看失败时怎么清理。

记录这些问题：

- 是否从用户态复制参数？在哪里检查大小和指针？
- 是否查找 GEM handle、KMS object id 或 syncobj handle？
- 查找后是否增加引用？
- 使用哪个锁保护对象？
- 失败时是否释放引用、unlock、unreserve？
- 返回给用户态的错误码是什么？

简化代码模式：

```c
obj = drm_gem_object_lookup(file, handle);
if (!obj)
    return -ENOENT;

ret = my_do_something(obj);

drm_gem_object_put(obj);
return ret;
```

如果中途有多个资源，就要画 error label：

```c
ret = step1();
if (ret)
    return ret;

ret = step2();
if (ret)
    goto err_step1;

ret = step3();
if (ret)
    goto err_step2;
```

错误路径是判断驱动质量和理解生命周期的关键。

### 6. 运行时验证

如果环境允许，可以用 `strace` 看用户态 ioctl：

```bash
strace -e openat,ioctl,mmap ./your_test
```

用 trace/dmesg 看内核侧：

```bash
sudo sh -c 'echo 0x1ff > /sys/module/drm/parameters/debug'
dmesg -w
```

或使用 ftrace 观察函数调用：

```bash
sudo trace-cmd record -p function_graph -g drm_ioctl -- ./your_test
sudo trace-cmd report
```

函数名和权限取决于内核配置。跑不了也没关系，静态路径表仍然是本节核心交付物。

### 7. 最终交付样板

把路径写成下面格式：

```text
ioctl 名称：
学习目标：

用户态：
- 调用函数：
- uapi 结构体：
- 输入字段：
- 输出字段：

DRM core：
- file_operations：
- 分发函数：
- descriptor：
- 权限检查：

驱动私有：
- handler：
- 关键对象：
- 锁：
- 引用计数：
- error path：

运行时证据：
- strace：
- dmesg：
- trace：

总结：
- 这条路径创建/修改/查询了什么对象：
- 最容易出错的地方：
- 可以迁移到其他 ioctl 的阅读方法：
```

这份样板以后可以复用到 `amdgpu_cs_ioctl`、`msm_gem_submit`、KMS atomic commit 等更复杂路径。

## 建议源码入口

- `libdrm/`
- `drivers/gpu/drm/drm_ioctl.c`
- `drivers/gpu/drm/drm_file.c`
- `drivers/gpu/drm/drm_gem.c`
- 目标驱动的 ioctl 表和处理函数。

## 建议输出

- 路径解剖笔记
- 关键函数列表

## 完成标准

- 能从用户态入口追到内核驱动处理函数。
- 能列出路径中出现的关键对象和引用关系。
- 能说明错误返回、锁、对象释放在哪些位置发生。

## 关联 Lab

- [Lab 22：完整读一次 `ioctl` 路径](../../labs/lab-22-end-to-end-ioctl-path/README.md)

## 下一步

进入 Session 23，基于已经建立的地图选择一个方向深入。

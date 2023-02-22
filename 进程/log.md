###        进程的基本知识

> 已经进入多进程阶段

##### 1.进程标识符uid
类型 pid_t

命令 ps

进程号是顺次向下使用

```c
    NAME
       getuid, geteuid - get user identity

    SYNOPSIS
       #include <unistd.h>
       #include <sys/types.h>

       uid_t getuid(void);
       uid_t geteuid(void);

    DESCRIPTION
       getuid() returns the real user ID of the calling process.

       geteuid() returns the effective user ID of the calling process.

    ERRORS
       These functions are always successful.
```



##### 2.进程的产生
    fork();
    
注意理解关键字：duplicating，意味着拷贝，克隆，一模一样等含义
fork后父子进程的区别：
- fork的返回值不一样
- pid不同
- ppid不同
- 未决信号和文件锁不继承
- 资源利用量清零

init进程：1号，是所有进程的祖先进程

    vfork():

##### 3.进程的消亡及释放资源

##### 4.exec函数族

##### 5.用户权限及组权限

##### 6.观摩课：解释器文件

##### 7.system();

##### 8.进程会计

##### 9.进程时间

##### 10.守护进程

##### 11.系统日志
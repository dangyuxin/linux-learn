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

调度器的调度策略决定哪个进程先运行

`fflush`的重要性

`vfork():`

##### 3.进程的消亡及释放资源

```
   wait();
   waitpid();
   waitid();
```

##### 4.exec函数族

```
   execl();
   execlp();
   execle();
   execv();
   execvp();
```

注意:`fflush`


##### 5.用户权限及组权限（u+s,g+s）
```c
   getuid();
   geteuid();
   getgid();
   geregid();
   setuid();
   setgid();
   setreuid();//原子化操作
   setregid();//交换
   seteuid();
   setegid();
```

##### 6.观摩课：解释器文件

##### 7.system();
理解  ：fork+exec+wait封装

##### 8.进程会计
acct();

##### 9.进程时间
times();

##### 10.守护进程
回话session，标识sid
终端
   setsid();
   getpgrd();
   getpgid();
   setgpid();

##### 11.系统日志

syslogd服务
openlog();
syslog();
closelog();


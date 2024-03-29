### 进程环境


#### 1.main函数

    int main(int argc,char **argv);


#### 2.进程的终止

##### 正常终止
- 从main函数返回
- 调用exit
- 调用_exit 或 _Exit
- 最后一个线程从其启动历程返回
- 最后一个线程调用pthread_exit
    
##### 异常终止
- 调用abort
- 接到一个信号并终止
- 最后一个线程对其取消请求做出响应

    `atexit();//钩子函数`

#### 3.命令行参数分析
    getopt();



#### 4.环境变量
    KEY = VALUE

    getenv();
    setenv();
    putenv();

#### 5.C程序的存储空间布局
    pmap(1);


#### 6.库
* 动态库
* 静态库
* 手工装载库

##### NAME

   `dlclose, dlopen, dlmopen - open and close a shared object`

##### SYNOPSIS

```c
  #include <dlfcn.h>

  void *dlopen(const char *filename, int flags);

  int dlclose(void *handle);

  #define _GNU_SOURCE
  #include <dlfcn.h>

  void *dlmopen(Lmid_t lmid, const char *filename, int flags);

  Link with -ldl.
```

#### 7.函数跳转
    goto;

    setjmp();

    longjup();

#### 8.资源的获取及其控制

##### NAME
       getrlimit, setrlimit, prlimit - get/set resource limits

##### SYNOPSIS
       #include <sys/time.h>
       #include <sys/resource.h>

       int getrlimit(int resource, struct rlimit *rlim);
       int setrlimit(int resource, const struct rlimit *rlim);

       int prlimit(pid_t pid, int resource, const struct rlimit *new_limit,
                   struct rlimit *old_limit);








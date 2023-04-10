## 并发（信号、线程）    
    
### 同步与异步

异步事件的处理：

* 查询法
* 通知法


#### 一、信号

##### 1.信号的概念

信号是软件的中断  
信号的响应依赖于中断  

##### 2.signal();

`void(*signal(int signum,void(*func)(int)))(int)`   
信号会打断阻塞的系统调用

##### 3.信号的不可靠

.

##### 4.可重入函数

所有的系统调用都是可重入的，一部分库函数也是可重入的，如`memcpy`.

##### 5.信号的响应过程

信号从收到到响应有一个不可避免的延迟  
思考：如何忽略掉一个信号的？  
标准信号为什么会丢失。  
标准信号的响应没有严格的顺序  
不能从信号处理函数中随意地往外跳（sigsetjump,siglongjump）



##### 6.常用函数

```bash
kill();
raise();
alarm();
pause();
abort();
system();

sleep();
nanosleep();
usleep();
select();

```

##### 7.信号集

```c
信号集类型：sigset_t

int sigemptyset(sigset_t *set);

int sigfillset(sigset_t *set);

int sigaddset(sigset_t *set, int signum);

int sigdelset(sigset_t *set, int signum);

int sigismember(const sigset_t *set, int signum);
```

##### 8.信号屏蔽字/pending的处理

`sigprocmask()`
`sigpending()`


##### 9.扩展

```bash
sigsuspend();
sigaction();
setitimer();
```

##### 10.实时信号

---


#### 线程


##### 1.线程的概念
> *一个正在运行的函数*

&emsp;posix线程是一套标准，而不是实现  
&emsp;openmp线程  
&emsp;线程标识：**pthread_t**   &emsp; :smile:  
&emsp;`pthread_equal();`  
&emsp;`pthread_self();`



##### 2.线程的创建
`pthread_create`  
线程的调度取决于线程调度器的策略

##### 线程的终止
3种方式:
- 线程从启动历程返回，返回值就是线程的退出码
- 线程可以被同一进程中的其他线程取消
- 线程调用`pthread_exit()`函数

`pthread_join()`  -->  `wait()`

##### 栈的清理

`pthread_cleanup_pop();`
`pthread_cleanup_push();`

##### 线程的取消选项

**线程取消**：`pthread_cancel();`   
取消有两种状态：允许和不允许  
允许取消又分为：异步cancel，推迟cancel（默认）--> 推迟至cancel点在响应  
cancel点：POSIX的cancel点，都是可能引发阻塞的系统调用  
`pthread_setcancelstate()`:设置线程是否可以取消  
`pthread_setcanceltype()`:设置取消方式   
`pthread_testcancel()`:本函数什么都不做，就是一个取消点   

线程分离: 
`pthread_detach()`:


##### 3.线程同步

互斥量：

- `pthread_mutex_t`
- `pthread_mutex_init()`
- `pthread_mutex_destory()`
- `pthread_mutex_lock()`
- `pthread_mutex_trylock()`
- `pthread_mutex_unlock()` 
- `pthread_once()`

条件变量：

- `pthread_con_t`
- `pthread_con_init()`
- `pthread_con_destroy()`
- `pthread_con_broadcast()`
- `pthread_con_signal()`

信号量：   
读写锁：读锁 --> 共享锁，写锁，互斥锁 

##### 4.线程属性
`pthread_attr_init()`  
`pthread_attr_destroy()`  
`pthread_attr_setstacksize()`  
`man`手册的`see also`  


##### 线程同步的属性
    互斥量属性：
- `pthread_mutexattr_init()`
- `pthread_mutexattr_destroy()`
- `pthread_mutexattr_getpshared()`
- `pthread_mutexattr_setpshared()`  
- `clone`
- `pthread_mutexattr_gettype()`
- `pthread_mutexattr_settype()`  
  
  条件变量属性和读写锁属性同上


##### 5.重入
**多线程中的IO**


##### 线程与信号
`pthread_sigmask()`
`sigwait()`
`pthread_kill`


##### 线程与fork


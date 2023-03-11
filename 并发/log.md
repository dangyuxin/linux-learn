## 并发（信号、线程）

### 同步与异步

异步事件的处理：

* 查询法
* 通知法


#### 一、信号

##### 1.信号的概念

信号是软件的中断  
信号的响应依赖于中断  

##### 2.signa();

`void(*signal(int signum,void(*func)(int)))(int)`  
信号会打断阻塞的系统调用

##### 3.信号的不可靠

##### 4.可重入函数

##### 5.信号的响应过程

##### 6.常用函数

```bash
kill();
raise();
alarm();
pause();
abort();
system();
```

##### 7.信号集

##### 8.信号屏蔽字/pending的处理

##### 9.扩展

```bash
sigsuspend();
sigaction();
setitimer();
```

##### 10.实时信号

---


### 并发
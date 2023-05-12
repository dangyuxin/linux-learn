## 高级IO

非阻塞IO -- 阻塞IO  
补充：有机状态机编程


##### 1.非阻塞IO
简单流程：自然流程是结构化的  
复杂流程：自然流程不是结构的

##### 2.IO多路转接
`select`
`poll`
`epoll`


##### 3.其他读写函数

```c
readv();
writev();
readn();
writen();
```

##### 4.存储映射IO
	mmap();
	munmap();

##### 5.文件锁

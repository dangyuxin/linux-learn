### 网络套接字socket

讨论： 跨主机的传输要注意的问题

##### 1.字节序问题：
- 大端：低地址处放高字节
- 小端：低地址处放低字节

主机字节序：host
网络字节序：network
解决：_to__: htons,htonl,ntohs,ntohl

##### 2.对齐

```c
struct {
	int i;
	float f;
	char ch;
};
```
解决：不对齐

##### 3.类型长度的问题：
int
char
解决：int32_t,uint32_t,int64_t,int8_t,...

SOCKET是什么：



##### 报式套接字

```c
socket();
bind();
sendto();
recvfrom();
inet_pton();
inet_ntop();
```

多点通讯：广播（全网广播，子网广播），多播/组播



##### 流式套接字

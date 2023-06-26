### TCP的粘包问题

* TCP传输是流式传输，传输过程中可能会遇到粘包的问题，所以我们要自己定义简单的协议
来保证每次传输的数据都是完整的.

我们可以约定一个包为长度加内容来保证client端和server端读取和发送的字节长度

```c
//client

int writen(int fd, const char *msg, int size)
{
    const char *buf = msg;
    int count = size;
    while (count > 0)
    {
        int len = send(fd, buf, count, 0);
        if (len == -1)
        {
            close(fd);
            return -1;
        }
        else if (len == 0)
            continue;
        buf += len;
        count -= len;
    }
    return size;
}

int sendMsg(int sd, char *msg, int len)
{
    if (msg == NULL || len <= 0 || sd <= 0)
        return -1;
    char *data = (char *)malloc(sizeof(char) * (len + 8));
    sprintf(data, "%08d%s", len, msg);
    int ret = writen(sd, data, len + 8);
    free(data);
    return ret;
}

```

```c
//server
int readn(int fd, char *buf, int size)
{
    char *pt = buf;
    int count = size;
    while (count > 0)
    {
        int len = recv(fd, pt, count, 0);
        if (len == -1)
            return -1;
        else if (len == 0)
            continue;
        pt += len;
        count -= len;
    }
    return size;
}

int recvMsg(int sd, char **msg)
{
    char lenBuf[8];
    readn(sd, lenBuf, 8);
    int len = atoi(lenBuf);
    printf("The msg size is %d \n", len);
    char *buf = (char *)malloc(sizeof(char) * len);
    int ret = readn(sd, buf, len);
    if (ret != len)
    {
        close(sd);
        free(buf);
        return -1;
    }
    *msg = buf;
    return ret;
}
```
- 其中，`readn()`和`writen()`都是保证每次传输读够多少的字节，server和client我们约定了一个协议，client先将长度加到字符串前面再发送，server接受到长度后再根据长度决定读取多少字节

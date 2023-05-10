#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "proto.h"

int main()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("socket()");
        exit(1);
    }

    struct sockaddr_in laddr, raddr;

    laddr.sin_family = AF_INET;
    laddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "0.0.0.0", &laddr.sin_addr.s_addr);

    bind(fd, (void *)&laddr, sizeof(laddr));

    listen(fd, 200);
    socklen_t len = sizeof(raddr);

    char arr[30];
    char buf[1024];
    while (1)
    {
        int new = accept(fd, (void *)&raddr, &len);
        inet_ntop(AF_INET, &raddr.sin_addr.s_addr, arr, sizeof(arr));
        if (new < 0)
        {
            perror("accept()");
            exit(1);
        }
        printf("This client is %s:%d\n", arr, ntohs(raddr.sin_port));

        int l = sprintf(buf, STAMP, (long long)time(NULL));
        send(new, buf, l, 0);
        close(new);
    }

    close(fd);
    exit(0);
}

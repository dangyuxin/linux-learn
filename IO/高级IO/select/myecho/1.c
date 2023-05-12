#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <unistd.h>

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
    laddr.sin_port = htons(8888);
    inet_pton(AF_INET, "0.0.0.0", &laddr.sin_addr.s_addr);

    bind(fd, (void *)&laddr, sizeof(laddr));

    listen(fd, 200);
    socklen_t len = sizeof(raddr);

    char arr[30];
    char buf[1024];
    fd_set rset;
    FD_ZERO(&rset);
    FD_SET(fd, &rset);
    int maxfd = fd;
    while (1)
    {
        fd_set t = rset;
        int count = select(maxfd + 1, &t, NULL, NULL, NULL);

        if (FD_ISSET(fd, &t))
        {
            int new = accept(fd, (void *)&raddr, &len);
            if (new < 0)
            {
                perror("accept()");
                exit(1);
            }
            FD_SET(new, &rset);
            maxfd = maxfd > new ? maxfd : new;
            inet_ntop(AF_INET, &raddr.sin_addr.s_addr, arr, sizeof(arr));

            printf("new:%d This client is %s:%d\n count:%d\n", new, arr, ntohs(raddr.sin_port), count);
        }

        for (int i = 3; i <= maxfd; i++)
        {
            if (i == fd)
                continue;
            if (FD_ISSET(i, &t))
            {
                int len = recv(i, buf, sizeof(buf), 0);
                printf("%s", buf);
                if (len < 0)
                {
                    perror("recv()");
                    continue;
                }
                if (len == 0)
                {
                    printf("The client is disconnecet...\n");
                    FD_CLR(i, &rset);
                    close(i);
                    break;
                }

                if (send(i, buf, strlen(buf) + 1, 0) < 0)
                {
                    perror("send()");
                    exit(1);
                }
            }
        }
    }

    close(fd);
    exit(0);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main()
{

    int sd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in laddr, raddr;
    laddr.sin_family = AF_INET;
    laddr.sin_port = htons(8888);
    inet_pton(AF_INET, "0.0.0.0", &laddr.sin_addr.s_addr);

    bind(sd, (void *)&laddr, sizeof(laddr));

    listen(sd, 128);

    int efd = epoll_create(128);
    struct epoll_event event, events[128];
    event.events = EPOLLIN | EPOLLET;
    event.data.fd = sd;
    epoll_ctl(efd, EPOLL_CTL_ADD, sd, &event);
    char arr[30];
    char buf[100];
    while (1)
    {
        int count = epoll_wait(efd, events, 128, -1);

        for (int i = 0; i < count; i++)
        {
            if (!events[i].events & EPOLLIN)
                continue;

            if (events[i].data.fd == sd)
            {
                socklen_t len = sizeof(raddr);

                int new = accept(sd, (void *)&raddr, &len);
                inet_ntop(AF_INET, &raddr.sin_addr.s_addr, arr, sizeof(arr));
                printf("This client is %s:%d\n", arr, htons(raddr.sin_port));
                event.data.fd = new;
                epoll_ctl(efd, EPOLL_CTL_ADD, new, &event);
            }
            else
            {
                int this = events[i].data.fd;

                int len = recv(this, buf, 100, 0);
                if (len == 0)
                {
                    printf("This client is disconnected\n");
                    epoll_ctl(efd, EPOLL_CTL_DEL, this, NULL);
                    close(this);
                }
                else
                {
                    printf("%s", buf);
                    send(this, buf, 100, 0);
                }
            }
        }
    }
}
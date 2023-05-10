#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

struct message
{
    char s[100];
};

int main()
{
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0)
    {
        perror("socket()");
        exit(1);
    }

    struct sockaddr_in raddr, saddr;

    raddr.sin_family = AF_INET;
    raddr.sin_port = htons(7777);
    inet_pton(AF_INET, "127.0.0.1", &raddr.sin_addr.s_addr);

    bind(fd, (void *)&raddr, sizeof(raddr));

    struct message a;
    char arr[30];

    socklen_t len = sizeof(saddr);
    while (1)
    {
        recvfrom(fd, &a, sizeof(a), 0, (void *)&saddr, &len);
        inet_ntop(AF_INET, &saddr.sin_addr.s_addr, arr, 30);
        printf("This message is from %s:%d\n", arr, ntohs(saddr.sin_port));
        puts(a.s);
    }

    close(fd);
    exit(0);
}
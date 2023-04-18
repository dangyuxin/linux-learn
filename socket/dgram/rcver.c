#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "proto.h"

int main()
{
    int sd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in laddr, raddr;
    struct msg_st rbuf;
    socklen_t len;

    if (sd < 0)
    {
        perror("socket()");
        exit(1);
    }

    laddr.sin_family = AF_INET;
    laddr.sin_port = htons(1996);
    inet_pton(AF_INET, "0.0.0.0", &laddr.sin_addr);

    if (bind(sd, (void *)&laddr, sizeof(laddr)) < 0)
    {
        perror("bind()");
        exit(1);
    }

    len = sizeof(raddr);

    char ipstr[40];
    while (1)
    {
        recvfrom(sd, &rbuf, sizeof(rbuf), 0, (void *)&raddr, &len);
        inet_ntop(AF_INET, &raddr.sin_addr, ipstr, 40);
        printf("--- Message from %s:%d---\n", ipstr, ntohl(raddr.sin_port));
        printf("Name: %s\n", rbuf.name);
        printf("Math: %d\n", htonl(rbuf.math));
        printf("Chinese: %d\n", htonl(rbuf.chinese));
    }
    close(sd);
    exit(0);
}
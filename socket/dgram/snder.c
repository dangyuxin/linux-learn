#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "proto.h"

int main(int argc, char **argv)
{
    int sd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in raddr;
    struct msg_st sbuf;
    socklen_t len;

    if (sd < 0)
    {
        perror("socket()");
        exit(1);
    }

    // bind()
    sbuf.math = htonl(100);
    sbuf.chinese = htonl(100);
    strcpy(sbuf.name, "DangYuXin");

    raddr.sin_family = AF_INET;
    raddr.sin_port = htons(1996);
    inet_pton(AF_INET, argv[1], &raddr.sin_addr);

    if (sendto(sd, &sbuf, sizeof(sbuf), 0, (void *)&raddr, sizeof(raddr)) < 0)
    {
        perror("1");
        exit(0);
    }

    puts("OK!");
    close(sd);
    exit(0);
}
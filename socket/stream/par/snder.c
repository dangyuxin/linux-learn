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

int main()
{
    struct sockaddr_in laddr;
    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0)
    {
        perror("socket()");
        exit(1);
    }

    laddr.sin_family = AF_INET;
    laddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "0.0.0.0", &laddr.sin_addr);

    // bind();

    if (connect(sd, (void *)&laddr, sizeof(laddr)) < 0)
    {
        perror("connect");
        exit(1);
    }

    FILE *fp = fdopen(sd, "r");
    if (fp == NULL)
    {
        perror("fdopen()");
        exit(1);
    }

    long long stamp;

    if (fscanf(fp, STAMP, &stamp) < 1)
        fprintf(stderr, "Bad format!\n");
    else
        fprintf(stdout, "%lld\n", stamp);

    fclose(fp);
    close(sd);
}

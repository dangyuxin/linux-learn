#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

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
    laddr.sin_port = htons(80);
    inet_pton(AF_INET, "127.0.0.1", &laddr.sin_addr);

    if (connect(sd, (void *)&laddr, sizeof(laddr)) < 0)
    {
        perror("connect");
        exit(1);
    }

    FILE *fp = fdopen(sd, "r+");
    if (fp == NULL)
    {
        perror("fdopen()");
        exit(1);
    }
    fprintf(fp, "GET /test.jpg\r\n\r\n");
    fflush(fp);

    char buf[1024];
    while (1)
    {
        int len = fread(buf, 1, 1024, fp);
        if (len <= 0)
            break;
        fwrite(buf, 1, 1024, stdout);
    }

    fclose(fp);
    close(sd);
}

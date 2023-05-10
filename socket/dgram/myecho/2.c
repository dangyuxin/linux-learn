#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

struct message
{
    char s[100];
};

int main(int argc, char **argv)
{
    int fd = socket(AF_INET, SOCK_DGRAM, 0);

    struct message a;
    strcpy(a.s, argv[1]);

    struct sockaddr_in raddr;

    raddr.sin_family = AF_INET;
    raddr.sin_port = htons(7777);
    inet_pton(AF_INET, "127.0.0.1", &raddr.sin_addr.s_addr);

    sendto(fd, &a, sizeof(a), 0, (void *)&raddr, sizeof(raddr));
    puts("OK");
    close(fd);

    exit(0);
}
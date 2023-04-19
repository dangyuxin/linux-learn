#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "usage...\n");
        exit(1);
    }

    struct in_addr inaddr;
    char buf[30];
    sscanf(argv[1], "%x", &inaddr.s_addr);
    inaddr.s_addr = htonl(inaddr.s_addr);
    inet_ntop(AF_INET, &inaddr, buf, 30);
    puts(buf);
    exit(0);
}
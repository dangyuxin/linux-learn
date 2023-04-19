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
    inet_pton(AF_INET, argv[1], &inaddr);
    printf("0x%x\n", ntohl(inaddr.s_addr));
    exit(0);
}
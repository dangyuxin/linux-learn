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

    laddr.sin_family = AF_INET;
    laddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "0.0.0.0", &laddr.sin_addr);

    bind(sd, &laddr, sizeof(laddr));

    listen(sd, 300);
}
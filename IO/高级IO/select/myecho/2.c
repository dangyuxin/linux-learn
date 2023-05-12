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
    laddr.sin_port = htons(8888);
    inet_pton(AF_INET, "0.0.0.0", &laddr.sin_addr);

    // bind();

    if (connect(sd, (void *)&laddr, sizeof(laddr)) < 0)
    {
        perror("connect");
        exit(1);
    }
    char buf[100];
    char back[100];
    while (1)
    {
        fgets(buf, 100, stdin);
        // buf[strlen(buf) - 1] = '\0';
        send(sd, buf, sizeof(buf), 0);

        int len = recv(sd, back, sizeof(buf), 0);
        if (len < 0)
        {
            perror("recv");
            exit(1);
        }
        printf("%s", back);
    }

    close(sd);
}

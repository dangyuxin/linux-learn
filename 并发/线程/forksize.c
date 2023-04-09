#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int i = 1;
void doo(void)
{
    printf("%d\n", i);
}

int main()
{

    int err;
    pid_t pid;
    while (i++)
    {
        pid = fork();
        if (pid == 0)
            exit(1);
        if (pid < 0)
        {
            atexit(doo);
            perror("fork()");
            exit(1);
        }
    }

    return 0;
}
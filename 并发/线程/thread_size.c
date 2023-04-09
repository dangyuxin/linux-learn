#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

int i = 1;
void *func(void *p)
{
    // write(1, "a", 1);
}
void doo(void)
{
    printf("%d\n", i);
}

int main()
{

    int err;
    pthread_t tid;
    atexit(doo);
    while (i++)
    {
        err = pthread_create(&tid, NULL, func, NULL);
        if (err)
        {
            fprintf(stderr, "%s\n", strerror(err));
            exit(1);
        }
    }

    return 0;
}
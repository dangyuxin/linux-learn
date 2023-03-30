#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

static void *fuc(void *)
{
    puts("Pthread is working!");
    return NULL;
}

int main()
{
    pthread_t tid;
    int err;
    puts("Begin!");
    err = pthread_create(&tid, NULL, fuc, NULL);
    if (err)
    {
        fprintf(stderr, "线程创建失败：%s\n", strerror(err));
        exit(1);
    }
    puts("End!");
    // sleep(1);
    exit(0);
}
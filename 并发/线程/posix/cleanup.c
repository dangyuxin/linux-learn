#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

static void clean(void *p)
{
    puts(p);
}

static void *fuc(void *)
{
    puts("Pthread is working!");
    pthread_cleanup_push(clean, "clean 1");
    pthread_cleanup_push(clean, "clean 2");
    pthread_cleanup_push(clean, "clean 3");
    puts("clean over!");
    // pthread_cleanup_pop(1);
    // pthread_cleanup_pop(0);
    // pthread_cleanup_pop(1);
    pthread_exit(NULL);
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(1);
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
    // sleep(1);
    pthread_join(tid, NULL);
    puts("End!");
    exit(0);
}
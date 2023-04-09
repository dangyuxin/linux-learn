#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "mysem.h"

#define LEFT 30000000
#define RIGHT 30000200
#define PNUM RIGHT - LEFT + 1
#define N 4
static mysem_t *sem;
static void *primer(void *p);

int main()
{
    pthread_t tid[PNUM];
    sem = mysem_init(N);
    int err;
    for (int i = LEFT; i <= RIGHT; ++i)
    {
        mysem_sub(sem, 1);
        err = pthread_create(tid + (i - LEFT), NULL, primer, (void *)i);
        if (err)
        {
            fprintf(stdin, "err\n");
            exit(1);
        }
        // pthread_join(tid[i - LEFT], NULL);
    }
    for (int i = LEFT; i <= RIGHT; ++i)
    {
        pthread_join(tid[i - LEFT], NULL);
    }
    mysem_destroy(sem);
    exit(0);
}

static void *primer(void *p)
{
    int mark = 1;
    int i = (int)p;
    for (int j = 2; j < i / 2; ++j)
    {
        if (i % j == 0)
        {
            mark = 0;
            break;
        }
    }
    if (mark)
    {
        printf("%d is a primer\n", i);
        fflush(NULL);
    }
    mysem_add(sem, 1);
    pthread_exit(NULL);
}
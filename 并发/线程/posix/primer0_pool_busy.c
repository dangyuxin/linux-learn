#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>

#define LEFT 30000000
#define RIGHT 30000200
#define PNUM 4

static int num = 0;
static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

static void *primer(void *p);

int main()
{
    pthread_t tid[PNUM];
    int err;
    for (int i = 0; i < PNUM; i++)
    {
        err = pthread_create(tid + i, NULL, primer, (void*)i);
        if (err)
        {
            fprintf(stdin, "err\n");
            exit(1);
        }
    }

    for (int i = LEFT; i <= RIGHT; i++) {
        pthread_mutex_lock(&mut);
        while (num != 0) {
            pthread_mutex_unlock(&mut);
            sched_yield();
            pthread_mutex_lock(&mut);
        }
        num = i;
        pthread_mutex_unlock(&mut);
    }
    pthread_mutex_lock(&mut);
    while (num != 0) {
        pthread_mutex_unlock(&mut);
        sched_yield();
        pthread_mutex_lock(&mut);
    }
    num = -1;
    pthread_mutex_unlock(&mut);

    for (int i = 0; i < PNUM; ++i)
    {
        pthread_join(tid[i], NULL);
    }
    pthread_mutex_destroy(&mut);
    exit(0);
}

static void *primer(void *p)
{
    while (1) {
        pthread_mutex_lock(&mut);
        while (num == 0) {
            pthread_mutex_unlock(&mut);
            sched_yield();
            pthread_mutex_lock(&mut);
        }
        if (num == -1) {
            pthread_mutex_unlock(&mut);
            break;
        }
        int i = num;
        num = 0;
        pthread_mutex_unlock(&mut);
        int mark = 1;
        for (int j = 2; j < i / 2; ++j)
        {
            if (i % j == 0)
            {
                mark = 0;
                break;
            }
        }
        if (mark) {
            printf("[%d] : %d is s primer\n", (int)p,i);
        }
    }
    pthread_exit(NULL);

}
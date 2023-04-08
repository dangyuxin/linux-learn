#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define LEFT 30000000
#define RIGHT 30000200
#define PNUM 4

static int num = 0;
static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

static void *primer(void *p);

struct st
{
    int a;
};

int main()
{
    pthread_t tid[PNUM];
    int err;
    struct st *p;
    void *fl;
    for (int i = 0; i <= num; ++i)
    {
        p = malloc(sizeof(*p));
        if (p == NULL)
        {
            perror("malloc()");
            exit(1);
        }
        p->a = i;
        err = pthread_create(tid + i, NULL, primer, p);
        if (err)
        {
            fprintf(stdin, "err\n");
            exit(1);
        }
        // pthread_join(tid[i - LEFT], NULL);
    }
    for (int i = 0; i <= num; ++i)
    {
        pthread_join(tid[i], &fl);
        free(fl);
    }
    pthread_mutex_destroy(&mut);
    exit(0);
}

static void *primer(void *p)
{
    int mark = 1;
    int i = ((struct st *)p)->a;
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
    }
    pthread_exit(p);
}
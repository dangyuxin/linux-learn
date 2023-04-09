#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define LEFT 30000000
#define RIGHT 30000200
#define PNUM RIGHT - LEFT + 1

static void *primer(void *p);

int main()
{
    pthread_t tid[PNUM];
    int err;
    for (int i = LEFT; i <= RIGHT; ++i)
    {
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
    }
    pthread_exit(NULL);
}
#include <stdio.h>
#include <stdlib.h>

#include "mysem.h"

struct mysem_t
{
    int val;
    pthread_mutex_t mut;
    pthread_cond_t cond;
}

mysem_t *mysem_init(int initval);
int mysem_add(mysem_t *, int val);
int mysem_sub(mysem_t *, int val);
int mysem_destroy(mysem_t *);
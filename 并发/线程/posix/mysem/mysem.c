#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "mysem.h"

typedef struct mysem_st
{
    int val;
    pthread_mutex_t mut;
    pthread_cond_t cond;
} sigc;

mysem_t *mysem_init(int initval)
{
    sigc *me;
    me = malloc(sizeof(*me));
    if (!me)
        return NULL;
    me->val = initval;
    pthread_mutex_init(&me->mut, NULL);
    pthread_cond_init(&me->cond, NULL);
    return me;
}
int mysem_add(mysem_t *head, int val)
{
    sigc *p = head;
    pthread_mutex_lock(&p->mut);
    p->val += val;
    pthread_mutex_unlock(&p->mut);
    pthread_cond_broadcast(&p->cond);
    return val;
}
int mysem_sub(mysem_t *head, int val)
{
    sigc *p = head;
    pthread_mutex_lock(&p->mut);
    while (p->val < val)
    {
        pthread_cond_wait(&p->cond, &p->mut);
    }
    p->val -= val;
    pthread_mutex_unlock(&p->mut);
    return val;
}
int mysem_destroy(mysem_t *head)
{
    sigc *p = head;
    pthread_mutex_destroy(&p->mut);
    pthread_cond_destroy(&p->cond);
    free(p);
    return 0;
}
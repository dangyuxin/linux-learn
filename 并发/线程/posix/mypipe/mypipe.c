#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "mypipe.h"

struct mypipe_st
{
    int head;
    int tail;
    char data[PIPESIZE];
    int datasize;
    int count_rd;
    int count_wd;
    pthread_mutex_t mut;
    pthread_cond_t cond;
};

mypipe_st *mypipe_init(void){
    struct mypipe_st *me;

    me = malloc(sizeof(*me));
    if (me == NULL)
        return NULL;

    me->head=0;
    me->tail=0;
    me->datasize=0;
    me->count_rd=0;
    me->count_wd=0;

    pthread_mutex_init(&me->mut,NULL);
    pthread_cond_init(&me->cond,NULL);

    return me;
}

int mypipe_register(mypipe_st* ptr,int opmap){
    /**If error*/ 
    struct mypipe_st *me = ptr;

    pthread_mutex_lock(&me->mut);
    if(opmap&MYPIPE_READ)
        me->count_rd++;     
    if(opmap&MYPIPE_WRITE)
        me->count_wd++;

    if(me->count_rd<=0||me->count_wd<=0)
        pthread_cond_wait(&me->cond,&me->mut);
    pthread_cond_broadcast(&me->cond);

    pthread_mutex_unlock(&me->mut);

    return 0;

}
int mypipe_unregister(mypipe_st*ptr,int opmap){
    struct mypipe_st *me = ptr;

    pthread_mutex_lock(&me->mut);
    
    if(opmap&me->count_rd)
        me->count_rd--;
    if(opmap&me->count_wd)
        me->count_wd--;

    pthread_mutex_unlock(&me->mut);

    return 0;
}


int next(int head){
    return 0;
}

static int mypipe_readbyte(struct mypipe_st *me ,char *datap){
    if(me->datasize <=0)
        return -1;

    *datap = me->data[me->head];
    me->head=next(me->head);
    me->datasize--;
    return 0;
}

int mypipe_read(mypipe_st *ptr,void *buf,size_t size){
    struct mypipe_st *me = ptr;
    int i;

    while(me->datasize<=0)
        pthread_cond_wait(&me->cond,&me->mut);
    
    for(i = 0; i < size; i++)
    {
        if(mypipe_readbyte(me,buf+i)!=0)
            break;
    }
    pthread_cond_broadcast(&me->cond);
    pthread_mutex_unlock(&me->mut);

    return i;
}

int mypipe_write(mypipe_st*ptr,const void*buf,size_t len){
    return 0;
}

int *mypipe_destroy(mypipe_st *ptr){
    struct mypipe_st *me = ptr;
        
    pthread_mutex_destroy(&me->mut);
    pthread_cond_destroy(&me->cond);

    free(ptr);
    return 0;
}

int main(){
    printf("Hello World\n");
}



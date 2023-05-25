#ifndef MYPIPE_H__
#define MYPIPE_H__

#include <stddef.h>
#define PIPESIZE 1024
#define MYPIPE_READ 0x00000001UL
#define MYPIPE_WRITE 0x00000002UL

typedef void mypipe_st;

mypipe_st *mypipe_init(void);

int mypipe_register(mypipe_st*,int opmap);
int mypipe_unregister(mypipe_st*,int opmap);

int mypipe_read(mypipe_st*,void *buf,size_t size);

int mypipe_write(mypipe_st*,const void*buf,size_t);

int *mypipe_destroy(mypipe_st *);

#endif 

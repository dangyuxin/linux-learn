#ifndef PROTO_H__
#define PROTO_H__
#define MAXNAME 11
#include <inttypes.h>

struct msg_st
{
    /* data */
    uint8_t name[MAXNAME];
    uint32_t math;
    uint32_t chinese;
};

#endif
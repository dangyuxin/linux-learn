#ifndef PROTO_H__
#define PROTO_H__

#define DEFAULT_MGROUP "224.2.2.2"
#define DEFAULT_RCVPORT "1996"

#define CHNNR 100
#define LISTCHNID 0
#define MINCHNID 1
#define MAXCHNID (MINCHNID + CHNNR - 1)

struct msg_channel_st
{
};

#endif
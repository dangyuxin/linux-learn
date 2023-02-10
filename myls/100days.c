#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1024

int main(){
    time_t stamp;
    struct tm *tm;
    char buf[MAX];
    time(&stamp);
    tm = localtime(&stamp);
    strftime(buf,MAX,"%Y-%m-%d",tm);
    puts(buf);
    tm->tm_mday+=100;
    (void)mktime(tm);
    strftime(buf,MAX,"%Y-%m-%d",tm);
    puts(buf);
    return 0;
}
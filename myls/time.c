#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define PATH "test.txt"
#define MAX 1024

int main(){
    FILE *fp;
    struct tm *tm;
    time_t stamp;
    int count = 0;
    char buf[MAX];

    fp = fopen(PATH,"a+");
    if((fp == NULL)){
        perror("fopen()");
        exit(1);
    }

    while(fgets(buf,MAX,fp)!=NULL){
        count++;
    }

    while(1){
        //time(&stamp);
        stamp = time(NULL);
        tm = localtime(&stamp);
        fprintf(fp,"%-4d%02d:%02d:%02d\n",++count,tm->tm_hour,tm->tm_min,tm->tm_sec);
        fflush(fp);
        sleep(1);
    }
    fclose(fp);
    return 0;
}
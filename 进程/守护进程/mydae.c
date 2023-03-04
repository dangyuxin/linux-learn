#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FNAME "./1.txt"

static int daemonize(){
    pid_t pid;
    pid = fork();
    if(pid<0){
        perror("fork()");
        return -1;
    }
    if(pid>0){
        exit(0);
    }

    setsid();
}

int main(){
    FILE *fp;
    if(daemonize())
        exit(1);
    fp = fopen(FNAME,"w");
    if(fp<0){
        perror("fopen()");
        exit(1);
    }
    for(int i;;i++){
        fprintf(fp,"%d\n",i);
        fflush(fp);
        sleep(1);
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
    pid_t a;
    printf("[%d],begin!\n",getpid());
    fflush(NULL);//!!!
    a = fork();
    if(a<0){
        perror("fork()");
        exit(1);
    }
    if(a==0){
        printf("[%d],child is working!\n",getpid());

    }
    else{
        //sleep(1);
        printf("[%d],parent is working!\n",getpid());
    }
    printf("[%d],end\n",getpid());
    //getchar();
    exit(0);
}
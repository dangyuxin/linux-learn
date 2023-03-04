#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define LEFT 30000000
#define RIGHT 30000200

int main(){
    pid_t pid;
    for(int i=LEFT;i<=RIGHT;++i){
        int mark=1;
        pid=fork();
        if(pid<0){
            perror("fork()");
            exit(1);
        }
        if(pid==0){
            for(int j=2;j<i/2;++j){
                if(i%j==0){
                    mark=0;
                    break;
                }
            }
            if(mark){
                printf("%d is a primer\n",i);
            }
            exit(0);//一定要写，否则子进程会继续进入循环创建进程
        }
    }
    //getchar();
    exit(0);
}
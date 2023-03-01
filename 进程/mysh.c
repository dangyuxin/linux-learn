#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define DELMITS " \t\n"

static void prompt(){
    printf("dyx-super shell$ ");
}
static void parse(const char *buf,glob_t *res){
    char *tok;
    int i=0;
    while(1){
    tok = strsep(&buf,DELMITS);
    if(tok==NULL){
        break;
    }
    if(tok[0]=='\0'){
        continue;
    }
    glob(tok,GLOB_NOCHECK|GLOB_APPEND*i,NULL,res);
    i=1;

    }
}
int main(){
    char *buf=NULL;
    size_t bufsize=0;
    glob_t res;
    pid_t pid;
    while(1){
        prompt();
        if(getline(&buf,&bufsize,stdin)<0){
            perror("getline");
            exit(1);
        }
        parse(buf,&res);
        if(0){//内部命令
            //do something
        }
        else{
            pid = fork();
            if(pid<0){
                perror("fork()");
                exit(1);
            }
            else if(pid==0){
                execvp(res.gl_pathv[0],res.gl_pathv);
                perror("execvp()");
                exit(1);
            }
            else{
                wait(NULL);
            }
        }
        
    }
}
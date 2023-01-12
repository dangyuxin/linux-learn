#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
static int64_t mydu(char *path){
    struct stat statres;
    if(lstat(path,&statres)<0){
        perror("lstat()");
        exit(1);
    }
    if(!S_ISDIR(statres.st_mode)){
        return statres.st_blocks/2;
    }   
    
}
int main(int argc, char **argv){
    if(argc<2){
        fprintf(stderr,"usage: ...\n");
        exit(1);
    }
    printf("%ld\n",mydu(argv[1]));
    return 0;
}
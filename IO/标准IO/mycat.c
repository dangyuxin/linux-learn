#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char **argv){
    if(argc<2){
        fprintf(stderr,"usage\n");
        exit(1);
    }
    FILE *fp;
    fp = fopen(argv[1],"r");
    if(fp==NULL){
        perror("fopen()");
        exit(1);
    }
    int ch;
    int i=0;
    while((ch=fgetc(fp))!=EOF){
        fputc(ch,stdout);
        fflush(NULL);
        i++;
        if(i%10==0){
            sleep(1);
        }

    }
    fclose(fp);
    exit(0);
}
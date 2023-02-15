#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX 1024

int main(int argc,char **argv){
    char buf[MAX];
    buf[0]='\0';
    int c;
    while(1){
        c = getopt(argc,argv,"a:lsRi");
        if(c<0)
            break;
        switch(c){
            case 'a' : strcat(buf,"展示隐藏文件\n");if(!strcmp(optarg,"a"))strcat(buf,"测一下对选项的进一步描述哈哈哈\n");break;
            case 'l' : strcat(buf,"以长格式进行输出\n");break;
            case 's' : strcat(buf,"展示文件大小\n");break;
            case 'R' : strcat(buf,"递归输出\n");break;
            case 'i' : strcat(buf,"打印文件的inode号\n");break;
            default : break;
        }
    }

    printf("%s",buf);
    
    return 0;
}
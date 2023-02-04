#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

void ls_i(const char *name){
    struct stat res;
    lstat(name,&res);
    printf("%ld ",res.st_ino);
    if(S_ISDIR(res.st_mode)){
        printf("\033[1;34m");  //设置文件夹为蓝色
    }
    else if(res.st_mode & S_IXGRP||res.st_mode & S_IXOTH || res.st_mode & S_IXUSR){
        printf("\033[1;32m");  //设置可执行文件为绿色
    }
    printf("%s   ",name);
    printf("\033[0m");  //将颜色设置为初始颜色
}

int main(int argc,char**argv){
    char filename[256];
    if(argc<2){
        strcpy(filename,".");
    }
    else{
        strcpy(filename,argv[1]);
    }
    DIR *d;
    d = opendir(filename);
    if(d==NULL){
        perror("opendir");
        exit(1);
    }
    struct dirent *ent;
    while((ent = readdir(d))!= NULL){
        if(ent->d_name[0]!='.')
            ls_i(ent->d_name);
    }
    putchar('\n');
    closedir(d);
    return 0;
    
}
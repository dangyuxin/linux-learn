#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define _a 0
#define _l 1
#define _i 2
#define _s 3
#define _t 4
#define _r 5
#define _R 6


/*
-a	列出目录下的所有文件，包括以.开头的隐含文件
-l	列出文件的详细信息（包括文件属性和权限等）
-R	使用递归连同目录中的子目录中的文件显示出来，如果要显示隐藏文件就要添加-a参数（列出所有子目录下的文件）
-t	按修改时间进行排序，先显示最后编辑的文件
-r	对目录反向排序（以目录的每个首字符所对应的ASCII值进行大到小排序）
-i	输出文件的i节点的索引信息
-s	在每个文件名后输出该文件的大小
*/
void print_file_info(const char *file_name,const char *path);
bool* lstype(int argc,char **argv,bool *type);
void ls_main(const char *path,bool *make);
void print(const char *path,struct stat sor);
int main(int argc, char **argv){
    int sig=1;
    bool *type=(bool*)malloc(sizeof(bool)*7);
    type[0]=false;
    type = lstype(argc,argv,type);
    for(int i=1;i<argc;i++){
        if(argv[i][0]!='-'){
            ls_main(argv[i],type);
            sig=0;
        }
    }
    if(sig){
        ls_main(".",type);
    }
    if(!type[_l]){
            putchar('\n');
        }
    free(type);
    return 0;
}
bool* lstype(int argc,char **argv,bool *type){
    for(int i=1;i<argc;i++){
        if(argv[i][0]!='-'){
            continue;
        }
        for(int j=1;j<strlen(argv[i]);j++){
            if(argv[i][j]=='a'){
                type[_a]=true;
            }
            if(argv[i][j]=='l'){
                type[_l]=true;
            }
            if(argv[i][j]=='i'){
                type[_i]=true;
            }
            if(argv[i][j]=='r'){
                type[_r]=true;
            }
            if(argv[i][j]=='s'){
                type[_s]=true;
            }
            if(argv[i][j]=='t'){
                type[_t]=true;
            }
            if(argv[i][j]=='R'){
                type[_R]=true;
            }
        }
    }
    return type;
}
void ls_main(const char *path,bool *make){
    DIR *dir;
    struct dirent *ent;
    struct stat res;
    int filecount = 0;
    char **files=(char**)malloc(sizeof(char**)*100000);
    dir = opendir(path);
    if(!dir){
        free(files);
        return ;
    }
    while((ent=readdir(dir))!=NULL){
        if(!make[_a]&&ent->d_name[0]=='.'){
            continue;
        }
        files[filecount]=(char*)malloc(sizeof(char)*1024);
        strcpy(files[filecount++],ent->d_name);
    }
    if(make[_t]){
        for(int i=0;i<filecount;i++){
            for(int j=0;j<filecount-i-1;j++){
                struct stat a,b;
                time_t a1,b1;
                lstat(files[j],&a);
                a1=a.st_mtime;
                lstat(files[j+1],&b);
                b1=b.st_mtime;               
                if(a1<b1){
                    char t[1024];
                    strcpy(t,files[j]);
                    strcpy(files[j],files[j+1]);
                    strcpy(files[j+1],t);
                }
            }
        }    
    }
    if(make[_r]){
        for(int i=0;i<filecount;i++){
            for(int j=0;j<filecount-i-1;j++){
                if(strcmp(files[j],files[j+1])<0){
                    char t[1024];
                    strcpy(t,files[j]);
                    strcpy(files[j],files[j+1]);
                    strcpy(files[j+1],t);
                }
            }
        }    
    }
        if(make[_R]){
            printf("%s:\n",path);
        }
        
    if(make[_s]||make[_l]){
        size_t size = 0;
        for(int i=0;i<filecount;i++){
        char *absl=(char*)malloc(sizeof(char)*1024);
        if(!strcmp(path,"/"))sprintf(absl,"/%s",files[i]);
        else sprintf(absl,"%s/%s",path,files[i]);
        if((lstat(absl,&res)==-1)){
            continue;
            perror("lstat");
            exit(1);
        }
        size+=res.st_blocks/2;
        free(absl);
        }
        printf("总用量 %ld\n",size);
    }
    for(int i=0;i<filecount;i++){
        char *absl=(char*)malloc(sizeof(char)*1024);
        if(!strcmp(path,"/"))sprintf(absl,"/%s",files[i]);
        else sprintf(absl,"%s/%s",path,files[i]);
        if((lstat(absl,&res)==-1)){
            continue;
            perror("lstat");
            exit(1);
        }
        if(make[_i]){
            printf("%ld ",res.st_ino);
        }
        if(make[_s]){
            printf("%3ld ",res.st_blocks/2);
        }
        if(make[_l]){
            print_file_info(absl,files[i]);
        }
        else{
            print(files[i],res);
            printf("  ");
        }
        free(absl);
    }
    for(int i=0;i<filecount;i++){
        char *absl=(char*)malloc(sizeof(char)*1024);
        if(!strcmp(path,"/"))sprintf(absl,"/%s",files[i]);
        else sprintf(absl,"%s/%s",path,files[i]);
        if((lstat(absl,&res)==-1)){
            continue;
            perror("lstat");
            exit(1);
        }
        if(make[_R]&&!(S_ISLNK(res.st_mode))&&S_ISDIR(res.st_mode)&&(strcmp(files[i],".")&&strcmp(files[i],".."))){
            putchar('\n');
            if(!make[_l])
                putchar('\n');
            ls_main(absl,make);
        }
        free(absl);
    }
    free(files);
    closedir(dir);
}
void print_file_info(const char *file_name ,const char *path){
    struct stat file_stat;
    struct passwd *pwd;
    struct group *grp;
    struct tm *tm;
    char date[20];

    if (lstat(file_name, &file_stat) == -1) {
        return ;
        perror("lstat");
        return;
    }
    if(S_ISLNK(file_stat.st_mode))printf("l");
    else if(S_ISREG(file_stat.st_mode))printf("-");
    else if(S_ISDIR(file_stat.st_mode))printf("d");
    else if(S_ISCHR(file_stat.st_mode))printf("c");
    else if(S_ISBLK(file_stat.st_mode))printf("b");
    else if(S_ISFIFO(file_stat.st_mode))printf("f");
    else if(S_ISSOCK(file_stat.st_mode))printf("s");
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
    printf(" %2ld", file_stat.st_nlink);
    pwd = getpwuid(file_stat.st_uid);
    grp = getgrgid(file_stat.st_gid);
    printf(" %s %s", pwd->pw_name, grp->gr_name);
    printf(" %5ld", file_stat.st_size);
    tm = localtime(&file_stat.st_mtime);
    strftime(date,sizeof(date), "%b %d %H:%M", tm);
    printf(" %s ", date);
    print(path,file_stat);
    putchar('\n');
}
void print(const char *path,struct stat sor){
    if (S_ISDIR(sor.st_mode)) {
        printf("\033[1;34m");  //设置文件夹为蓝色
    } else if ((sor.st_mode & S_IXUSR) || (sor.st_mode & S_IXGRP) || (sor.st_mode & S_IXOTH)) {
        printf("\033[1;32m");  //设置可执行文件为绿色
    } 
    if(S_ISLNK(sor.st_mode)){
        printf("\033[1;36m"); //链接文件颜色显示
    }  
    printf("%s\033[0m", path); //将颜色设置恢复为默认
}

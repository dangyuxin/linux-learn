#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
int get_line(FILE *fp){
	int line = 0;
	fseek(fp,0,SEEK_SET);
	int ch;
	while(1){
		ch=fgetc(fp);
		if(ch=='\n'){
			line++;
		}
		if(ch==EOF){
			return line;
		}
	}
}
int move_line(FILE *fp,int line){
	int n=1;
	fseek(fp,0,SEEK_SET);
	while(1){
		if(n==line){
			return 0;
		}
		int ch;
		ch = fgetc(fp);
		if(ch=='\n'){
			n++;
		}
	}
}
int main(int argc,char **argv){
	FILE *fp;
	if(argc<2){
		fprintf(stderr,"usage: %s filename",argv[0]);
		exit(1);
	}
	fp = fopen(argv[1],"r+");
	if(fp == NULL){
		perror("fopen()");
		exit(1);
	}
	FILE *fp1;
	fp1= fopen(argv[1],"r+");
	if(fp1==NULL){
		fclose(fp);
		perror("fopen(fp1)");
		exit(1);
	}
	printf("请输入你要删除的行数\n");
	int line;
	scanf("%d",&line);
	move_line(fp,line);
	move_line(fp1,line+1);
	int ch;
	while(1){
		ch=fgetc(fp1);
		if(ch==EOF){
			break;
		}
		fputc(ch,fp);
	}
	int fd= fileno(fp);
	int size = lseek(fd,0,SEEK_CUR);
	ftruncate(fd,size);
	//int line=get_line(fp);
	//printf("%d\n",line);
	//move_line(fp,5);
	//printf("%ld\n",ftell(fp));
	fclose(fp);
	fclose(fp1);
	exit(0);
}

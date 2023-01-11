#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 1024

int main(int argc, char **argv){
	int sfd,dfd;
	char buf[BUFSIZE];
	int len ,ret,pos;
	if(argc<3){
		fprintf(stderr,"Usage %s s_file d_file\n",argv[0]);
		exit(1);
	}
	sfd=open(argv[1],O_RDONLY);
	if(sfd<0){
		perror("fopen");
		exit(1);
	}
	dfd=open(argv[2],O_WRONLY|O_CREAT,O_TRUNC,0600);
	if(dfd<0){
		close(sfd);
		perror("fopen");
		exit(1);
	}
	while(1){
		len=read(sfd,buf,BUFSIZE);
		if(len<0){
			perror("read");
			break;
		}
		if(len==0)
			break;
		ret=write(dfd,buf,len);
		if(ret<0){
			perror("write");
			break;
		}
	}
	close(dfd);
	close(sfd);
	exit(0);
}

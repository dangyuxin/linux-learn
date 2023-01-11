#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
 
 
int get_line(int fd)
{
	int line = 0,prev,ret;
	char ch;
 
	prev = lseek(fd,0,SEEK_CUR);	//save last seek
	lseek(fd,0,SEEK_SET);
	while(1)
	{
		ret = read(fd, &ch,1);
		if(ret <= 0)
		{
			lseek(fd,prev,SEEK_SET);
			return line;
		}
		if(ch == '\n')
			line++;
	}
}
 
int move_line(int fd,int line)
{
	char ch;
	int n = 1,ret;
 
	while(1)
	{
		if(n == line)
			return 0;
		ret = read(fd,&ch,1);
		if(ret <= 0)
			return -1;
		if(ch == '\n')	
		{
			n++;
		}	
	}
}
 
 
int main(int argc, char **argv)
{
	int fd_r,fd_w;
	int ret,size,del_line;
	char ch;
 
	if(argc < 2)
	{
		fprintf(stderr,"Usage:%s <filename>\n",argv[0]);
		exit(1);
	}
 
	fd_r = open(argv[1],O_RDONLY);
	if(fd_r < 0)
	{
		perror("open()");
		exit(1);
	}
 
	fd_w = open(argv[1],O_RDWR,0666);
	if(fd_w < 0)
	{
		close(fd_r);
		perror("open()");
		exit(1);
	}
 
	printf("which line you wanna del:");
	scanf("%d",&del_line);
 
	move_line(fd_w,del_line);
	move_line(fd_r,del_line + 1);
 
	while(1)
	{
		ret = read(fd_r,&ch,1);
		if(ret <= 0)
			break;
		write(fd_w,&ch,1);
	}
 
	if(ret < 0)
	{
		perror("read");
		exit(1);
	}
 
	size = lseek(fd_w,0,SEEK_CUR);
	ftruncate(fd_w,size);	
 
	close(fd_r);
	close(fd_w);
	return 0;
}

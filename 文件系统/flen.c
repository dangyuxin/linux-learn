#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static off_t flen(char *file){
	struct stat filestat;
	if(stat(file,&filestat)<0){
		perror("stat()");
		exit(1);
	}
	return filestat.st_size;
}
int main(int argc,char **argv){
	if(argc<2){
		fprintf(stderr,"Usage %s filename\n",argv[0]);
		exit(1);
	}
	printf("%ld\n",flen(argv[1]));
	return 0;
}

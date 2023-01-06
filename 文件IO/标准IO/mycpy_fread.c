#include <stdio.h>
#include <stdlib.h>
#define SIZE 1024
int main(int argc,char **argv){
	FILE *fps,*fpd;
	int n;
	char buf[SIZE];
	if(argc<3){
		fprintf(stderr,"Usage:%s src_file dest_file\n",argv[0]);
		exit(1);
	}
	fps=fopen(argv[1],"r");
	if(fps==NULL){
		perror("fopen");
		exit(1);
	}
	fpd=fopen(argv[2],"w");
	if(fpd==NULL){
		fclose(fps);
		perror("fopen");
		exit(1);
	}
	while(n=fread(buf,1,SIZE,fps)>0){
		fwrite(buf,1,SIZE,fpd);
	}
	fclose(fpd);
	fclose(fps);
	exit(0);
}

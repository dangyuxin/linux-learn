#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv){
	FILE *fp;
	char *linebuf=NULL;
	size_t linesize=0;
	if(argc<2){
		fprintf(stderr,"usage:%s filename1\n",argv[0]);
		exit(1);
	}
	fp=fopen(argv[1],"r");
	if(fp==NULL){
		perror("fopen()");
		exit(1);
	}
	while(1){
		if(getline(&linebuf,&linesize,fp)<0)
			break;
        fprintf(stdout,"%s",linebuf);
		fprintf(stdout,"%ld\n",strlen(linebuf));
		fprintf(stdout,"%ld\n",linesize);
	}

	fclose(fp);
	return 0;
}
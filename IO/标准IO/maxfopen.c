#include <stdio.h>
#include <stdlib.h>
int main()
{
	FILE *fp;
	int count=0;
	while(1){
		fp=fopen("1.txt","r");
		if(fp==NULL){
			perror("fopen");
			break;
		}
		count++;
	}
	printf("count=%d\n",count);
	return 0;
}

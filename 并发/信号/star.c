#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(){

	signal(SIGINT,SIG_IGN);
	for(int i=0;i<10;i++){
		printf("*");
		fflush(NULL);
		sleep(1);
	}
	exit(0);
}

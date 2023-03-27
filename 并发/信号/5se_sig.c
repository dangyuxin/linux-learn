#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static int loop = 1;
static void handler(int s){
	loop=0;
}
int main(){

	int64_t count=0;
	alarm(5);
	signal(SIGALRM,handler);
	while(loop)
		++count;
	printf("%ld\n",count);
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	time_t end = time(NULL) + 5;
	int64_t count=0;
	while(time(NULL)<end){
		++count;
	}
	printf("%ld\n",count);
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(){
	char s[1024];
	size_t a;
	while(1){
		a = read(0,s,1);
		if(a<=0){
			break;
		}
		write(1,s,1);	
	}
	exit(1);
}

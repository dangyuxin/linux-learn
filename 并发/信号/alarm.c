#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	alarm(2);
	while(1);
	exit(0);
}

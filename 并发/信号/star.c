#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void int_handler(int s)
{
	write(1, "!", 1);
}

int main()
{

	// signal(SIGINT,SIG_IGN);
	signal(SIGINT, int_handler);
	for (int i = 0; i < 10; i++)
	{
		printf("*");
		fflush(NULL);
		sleep(1);
	}
	exit(0);
}

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
	sigset_t set, saveset;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigprocmask(SIG_UNBLOCK, &set, &saveset);
	signal(SIGINT, int_handler);
	for (int j = 0; j < 1000; j++)
	{
		sigprocmask(SIG_BLOCK, &set, NULL);
		for (int i = 0; i < 5; i++)
		{
			printf("*");
			fflush(NULL);
			sleep(1);
		}
		printf("\n");
		sigprocmask(SIG_UNBLOCK, &set, NULL);
	}
	sigprocmask(SIG_SETMASK, &saveset, NULL);
	exit(0);
}

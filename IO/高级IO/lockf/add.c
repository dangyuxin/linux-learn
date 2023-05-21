#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define PNUM 20
#define SIZE 1024

static void add()
{
	FILE *fp;
	char buf[SIZE];
	fp = fopen("add.txt", "r+");
	if (fp == NULL)
	{
		perror("fopen()");
		exit(1);
	}
	int fd = fileno(fp);

	lockf(fd, F_LOCK, 0);
	fgets(buf, SIZE, fp);
	fseek(fp, 0, SEEK_SET);
	sleep(1);
	fprintf(fp, "%d\n", atoi(buf) + 1);
	fflush(fp);
	lockf(fd, F_ULOCK, 0);

	fclose(fp);
	return;
}

int main()
{
	int i, pid;
	for (int i = 0; i < PNUM; i++)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork()");
			exit(1);
		}

		if (pid == 0)
		{
			add();
			exit(0);
		}
	}
	for (i = 0; i < PNUM; i++)
	{
		wait(NULL);
	}
	exit(0);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MEMSIZE 1024

int main()
{
	char *ptr = mmap(NULL, MEMSIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	if (ptr == MAP_FAILED)
	{
		perror("mmap()");
		exit(1);
	}
	pid_t pid = fork();
	if (pid < 0)
	{
		perror("fork()");
		munmap(ptr, MEMSIZE);
		exit(1);
	}

	if (pid == 0)
	{
		strcpy(ptr, "Hello!");
		munmap(ptr, MEMSIZE);
		exit(0);
	}
	else
	{
		wait(NULL);
		puts(ptr);
		munmap(ptr, MEMSIZE);
	}
	exit(0);
}

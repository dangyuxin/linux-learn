#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s  filename\n", argv[0]);
		exit(1);
	}

	int count = 0;

	int fd = open(argv[1], O_RDONLY);

	struct stat res;
	fstat(fd, &res);

	char *str = mmap(NULL, res.st_size, PROT_READ, MAP_SHARED, fd, 0);

	close(fd);

	for (int i = 0; i < res.st_size; i++)
	{
		if (str[i] == 'a')
			count++;
	}
	printf("%d\n", count);

	munmap(str, res.st_size);

	exit(0);
}

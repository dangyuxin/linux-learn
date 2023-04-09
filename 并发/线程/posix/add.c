#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define PNUM 20
#define SIZE 1024

static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

static void *add(void *p)
{
	FILE *fp;
	char buf[SIZE];
	fp = fopen("add.txt", "r+");
	if (fp == NULL)
	{
		perror("fopen()");
		exit(1);
	}

	// pthread_mutex_lock(&mut);
	fgets(buf, SIZE, fp);
	fseek(fp, 0, SEEK_SET);
	fprintf(fp, "%d\n", atoi(buf) + 1);
	fclose(fp);
	// pthread_mutex_unlock(&mut);
	pthread_exit(NULL);
}

int main()
{
	int i, err;
	pthread_t tid[PNUM];
	for (int i = 0; i < PNUM; i++)
	{
		err = pthread_create(tid + i, NULL, add, NULL);
		if (err)
		{
			fprintf(stderr, "pthread_create():%s\n", strerror(err));
			exit(1);
		}
	}
	for (i = 0; i < PNUM; i++)
	{
		pthread_join(tid[i], NULL);
	}

	pthread_mutex_destroy(&mut);
	exit(1);
}
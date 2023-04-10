#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define PNUM 4

static pthread_mutex_t mut[PNUM];

static void *func(void *p)
{
	int n = (int)p;
	int c = n + 'a';
	while (1)
	{
		pthread_mutex_lock(mut + n);
		write(1, &c, 1);
		pthread_mutex_unlock(mut + (n + 1) % 4);
	}
	pthread_exit(NULL);
}

int main()
{
	pthread_t tid[PNUM];
	int i, err;
	for (i = 0; i < PNUM; i++)
	{
		pthread_mutex_init(mut + i, NULL);
		pthread_mutex_lock(mut + i);
		err = pthread_create(tid + i, NULL, func, (void *)i);
		if (err)
		{
			fprintf(stderr, "pthread_create() %s\n", strerror(err));
			exit(1);
		}
	}

	pthread_mutex_unlock(mut);

	alarm(5);

	for (i = 0; i < PNUM; i++)
	{
		pthread_join(tid[i], NULL);
	}

	exit(0);
}
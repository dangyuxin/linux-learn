#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define PNUM 4

static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t con = PTHREAD_COND_INITIALIZER;

static int num = 0;

static void *func(void *p)
{
	int n = (int)p;
	int c = n + 'a';
	while (1)
	{
		pthread_mutex_lock(&mut);
		while (n != num)
			pthread_cond_wait(&con, &mut);
		write(1, &c, 1);
		num = (num + 1) % 4;
		pthread_mutex_unlock(&mut);
		pthread_cond_broadcast(&con);
	}
	pthread_exit(NULL);
}

int main()
{
	pthread_t tid[PNUM];
	int i, err;
	for (i = 0; i < PNUM; i++)
	{
		err = pthread_create(tid + i, NULL, func, (void *)i);
		if (err)
		{
			fprintf(stderr, "pthread_create() %s\n", strerror(err));
			exit(1);
		}
	}

	alarm(5);

	for (i = 0; i < PNUM; i++)
	{
		pthread_join(tid[i], NULL);
	}

	pthread_cond_destroy(&con);
	pthread_mutex_destroy(&mut);
	exit(0);
}
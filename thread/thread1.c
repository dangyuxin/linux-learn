#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX 1024

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static void *producer(void *p)
{
    FILE *fp;
    char buf[MAX];
    while (1)
    {
        pthread_mutex_lock(&mutex);
        fp = fopen("1.txt", "r+");
        if (fp == NULL)
        {
            perror("fopen()");
            exit(1);
        }
        while (atoi(fgets(buf, MAX, fp)) >= 500)
        {
            fseek(fp, 0, SEEK_SET);
            pthread_cond_wait(&cond, &mutex);
        }
        fseek(fp, 0, SEEK_SET);
        fprintf(fp, "%d", atoi(buf) + 1);
        fflush(fp);
        fclose(fp);
        pthread_mutex_unlock(&mutex);
        pthread_cond_broadcast(&cond);
    }
    pthread_exit(NULL);
}

static void *consumer()
{
    FILE *fp;
    char buf[MAX];
    while (1)
    {
        pthread_mutex_lock(&mutex);
        fp = fopen("1.txt", "r+");
        if (fp == NULL)
        {
            perror("fopen()");
            exit(1);
        }
        while (atoi(fgets(buf, MAX, fp)) <= 150)
        {
            fseek(fp, 0, SEEK_SET);
            pthread_cond_wait(&cond, &mutex);
        }
        fseek(fp, 0, SEEK_SET);
        fprintf(fp, "%d\n", atoi(buf) - 1);
        fflush(fp);
        fclose(fp);
        pthread_mutex_unlock(&mutex);
        pthread_cond_broadcast(&cond);
    }
    pthread_exit(NULL);
}

int main()
{

    pthread_t tid[4];
    pthread_create(tid, NULL, producer, NULL);
    pthread_create(tid + 1, NULL, consumer, NULL);
    pthread_create(tid + 2, NULL, producer, NULL);
    pthread_create(tid + 3, NULL, consumer, NULL);
    for (int i = 0; i < 4; i++)
    {
        pthread_join(tid[i], NULL);
    }
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);
    exit(0);
}
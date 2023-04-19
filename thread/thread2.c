#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

typedef struct SPSCQueue
{
    /* Define Your Data Here */
    int front;
    int rear;
    int cap;
    int *date;
    pthread_mutex_t mutex;
    pthread_cond_t cond;

} SPSCQueue;

SPSCQueue *SPSCQueueInit(int capacity)
{
    SPSCQueue *t = (SPSCQueue *)malloc(sizeof(SPSCQueue));
    t->cap = capacity + 1;
    t->date = (int *)malloc(sizeof(int) * capacity);
    t->front = 0;
    t->rear = 0;
    pthread_mutex_init(&t->mutex, NULL);
    pthread_cond_init(&t->cond, NULL);

    return t;
}
void SPSCQueuePush(SPSCQueue *queue, int s)
{
    pthread_mutex_lock(&queue->mutex);
    if ((queue->rear + 1) % queue->cap == queue->front)
    {
        pthread_cond_wait(&queue->cond, &queue->mutex);
    }
    queue->date[queue->rear] = s;
    queue->rear = (queue->rear + 1) % queue->cap;
    printf("[p]当前队列元素数量：%d\n", (queue->rear - queue->front + queue->cap) % queue->cap);
    fflush(NULL);
    pthread_mutex_unlock(&queue->mutex);
    pthread_cond_broadcast(&queue->cond);
}
int SPSCQueuePop(SPSCQueue *queue)
{
    pthread_mutex_lock(&queue->mutex);
    if (queue->front == queue->rear)
    {
        pthread_cond_wait(&queue->cond, &queue->mutex);
    }
    int p = queue->date[queue->front];
    queue->front = (queue->front + 1) % queue->cap;
    printf("[c]当前队列元素数量：%d\n", (queue->rear - queue->front + queue->cap) % queue->cap);
    fflush(NULL);
    pthread_mutex_unlock(&queue->mutex);
    pthread_cond_broadcast(&queue->cond);
    return p;
}

void SPSCQueueDestory(SPSCQueue *queue)
{
    free(queue->date);
    pthread_cond_destroy(&queue->cond);
    pthread_mutex_destroy(&queue->mutex);
    free(queue);
    queue = NULL;
}

void *consumer(void *p)
{
    SPSCQueue *t = (SPSCQueue *)p;
    while (1)
    {
        SPSCQueuePop(t);
        sleep(rand() % 3);
    }
}

void *producer(void *p)
{
    SPSCQueue *t = (SPSCQueue *)p;
    while (1)
    {
        SPSCQueuePush(t, rand() % 10);
        sleep(rand() % 3);
    }
}

int main()
{
    SPSCQueue *q = SPSCQueueInit(100);
    pthread_t tid1, tid2, tid3;
    pthread_create(&tid2, NULL, producer, (void *)q);
    sleep(10);
    pthread_create(&tid1, NULL, consumer, (void *)q);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    SPSCQueueDestory(q);
    return 0;
}

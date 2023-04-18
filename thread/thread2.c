#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5
int queue[N];
sem_t blank_number, product_number; // 两个信号量控制
void *producer(void *arg)           // 生产
{
    int p = 0;
    while (1)
    {
        sem_wait(&blank_number);      // 空格的位置-1
        queue[p] = rand() % 1000 + 1; // 放入队列
        printf("product %d \n", queue[p]);
        sem_post(&product_number); // 生产的数量+1
        p = (p + 1) % N;           // 1-N 1-N 循环放入 模拟队列
        sleep(rand() % 5);
    }
}
void *consumer(void *arg) // 消费者
{
    int c = 0;
    while (1)
    {
        sem_wait(&product_number); // 产品数量-1
        printf("Consume %d\n", queue[c]);
        queue[c] = 0;
        sem_post(&blank_number); // 空格数量+1
        c = (c + 1) % N;
        sleep(rand() % 5);
    }
}
int main()
{
    sem_init(&blank_number, 0, N);   // 空格的数量(剩余空间的位置)
    sem_init(&product_number, 0, 0); // 已经生产的数量
    pthread_t pid, cid;
    pthread_create(&pid, NULL, producer, NULL);
    pthread_create(&cid, NULL, consumer, NULL);
    pthread_join(pid, NULL);
    pthread_join(cid, NULL);
}

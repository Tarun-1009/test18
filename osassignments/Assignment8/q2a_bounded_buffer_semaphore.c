#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define SIZE 10

// Assignment 8 - Q2(a): Bounded Buffer using Semaphores
int buf[SIZE][2]; // [producer_id, iteration]
int in = 0, out = 0;
sem_t empty, full;
pthread_mutex_t mutex;

void *producer(void *arg) {
    long id = (long)arg;
    for (int i = 1; i <= 20; i++) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buf[in][0] = id;
        buf[in][1] = i;
        in = (in + 1) % SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    long id = (long)arg;
    for (int i = 1; i <= 10; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int prod_id = buf[out][0];
        int iter = buf[out][1];
        out = (out + 1) % SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        printf("Consumer %ld read from Producer %d (Iter %d)\n", id, prod_id, iter);
    }
    pthread_exit(NULL);
}

int main() {
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_t p[5], c[10];
    for (long i = 1; i <= 5; i++) pthread_create(&p[i-1], NULL, producer, (void *)i);
    for (long i = 1; i <= 10; i++) pthread_create(&c[i-1], NULL, consumer, (void *)i);

    for (int i = 0; i < 5; i++) pthread_join(p[i], NULL);
    for (int i = 0; i < 10; i++) pthread_join(c[i], NULL);

    return 0;
}

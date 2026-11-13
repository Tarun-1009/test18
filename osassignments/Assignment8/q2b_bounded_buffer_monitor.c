#include <stdio.h>
#include <pthread.h>

#define SIZE 10

// Assignment 8 - Q2(b): Bounded Buffer using Monitor
int buf[SIZE][2];
int in = 0, out = 0, count = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;

void insert(int id, int iter) {
    pthread_mutex_lock(&lock);
    while (count == SIZE) pthread_cond_wait(&not_full, &lock);
    buf[in][0] = id;
    buf[in][1] = iter;
    in = (in + 1) % SIZE;
    count++;
    pthread_cond_signal(&not_empty);
    pthread_mutex_unlock(&lock);
}

void remove_item(long cons_id) {
    pthread_mutex_lock(&lock);
    while (count == 0) pthread_cond_wait(&not_empty, &lock);
    int prod_id = buf[out][0];
    int iter = buf[out][1];
    out = (out + 1) % SIZE;
    count--;
    pthread_cond_signal(&not_full);
    pthread_mutex_unlock(&lock);

    printf("Consumer %ld read from Producer %d (Iter %d)\n", cons_id, prod_id, iter);
}

void *producer(void *arg) {
    long id = (long)arg;
    for (int i = 1; i <= 20; i++) insert(id, i);
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    long id = (long)arg;
    for (int i = 1; i <= 10; i++) remove_item(id);
    pthread_exit(NULL);
}

int main() {
    pthread_t p[5], c[10];
    for (long i = 1; i <= 5; i++) pthread_create(&p[i-1], NULL, producer, (void *)i);
    for (long i = 1; i <= 10; i++) pthread_create(&c[i-1], NULL, consumer, (void *)i);

    for (int i = 0; i < 5; i++) pthread_join(p[i], NULL);
    for (int i = 0; i < 10; i++) pthread_join(c[i], NULL);

    return 0;
}

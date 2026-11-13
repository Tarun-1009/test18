/*
 * Thread-Safe Shared Counter Using pthread_mutex_t vs stdatomic.h in C
 */

#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>

#define NUM_THREADS 4
#define ITERS 50000

int mutex_counter = 0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
atomic_int atomic_counter = 0;

void *increment_both(void *arg) {
    (void)arg;
    for (int i = 0; i < ITERS; i++) {
        pthread_mutex_lock(&mtx);
        mutex_counter++;
        pthread_mutex_unlock(&mtx);

        atomic_fetch_add_explicit(&atomic_counter, 1, memory_order_relaxed);
    }
    return NULL;
}

int main(void) {
    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_both, NULL);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Expected       = %d\n", NUM_THREADS * ITERS);
    printf("Mutex counter  = %d\n", mutex_counter);
    printf("Atomic counter = %d\n", atomic_load(&atomic_counter));
    return 0;
}


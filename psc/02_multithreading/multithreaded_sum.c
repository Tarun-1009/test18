/*
 * Parallel Array Sum Using POSIX Threads
 *
 * Splits an array across 4 worker threads and combines partial sums.
 */

#include <pthread.h>
#include <stdio.h>

#define ARR_SIZE 1000
#define NUM_THREADS 4

int arr[ARR_SIZE];
long partial_sum[NUM_THREADS];

void *sum_chunk(void *arg) {
    int tid = *(int *)arg;
    int chunk = ARR_SIZE / NUM_THREADS;
    int start = tid * chunk;
    int end = (tid == NUM_THREADS - 1) ? ARR_SIZE : start + chunk;

    long s = 0;
    for (int i = start; i < end; i++) {
        s += arr[i];
    }
    partial_sum[tid] = s;
    return NULL;
}

int main(void) {
    for (int i = 0; i < ARR_SIZE; i++) {
        arr[i] = i + 1;
    }

    pthread_t threads[NUM_THREADS];
    int tids[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        tids[i] = i;
        pthread_create(&threads[i], NULL, sum_chunk, &tids[i]);
    }

    long total = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        total += partial_sum[i];
    }

    printf("Parallel sum of 1..%d = %ld\n", ARR_SIZE, total);
    return 0;
}


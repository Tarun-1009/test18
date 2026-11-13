/*
 * Prefix Product Using N POSIX Threads in C
 *
 * Usage: ./prefix_product 2 3 4 5
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    long long *nums;
    long long *results;
} Task;

void *compute_prefix(void *arg) {
    Task *t = (Task *)arg;
    long long prod = 1;
    for (int j = 0; j < t->id; j++) {
        prod *= t->nums[j];
    }
    t->results[t->id - 1] = prod;
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <n1> <n2> ...\n", argv[0]);
        return 1;
    }

    int N = argc - 1;
    long long *nums = (long long *)malloc((size_t)N * sizeof(long long));
    long long *results = (long long *)malloc((size_t)N * sizeof(long long));
    pthread_t *threads = (pthread_t *)malloc((size_t)N * sizeof(pthread_t));
    Task *tasks = (Task *)malloc((size_t)N * sizeof(Task));

    for (int i = 0; i < N; i++) {
        nums[i] = atoll(argv[i + 1]);
    }

    for (int i = 0; i < N; i++) {
        tasks[i].id = i + 1;
        tasks[i].nums = nums;
        tasks[i].results = results;
        pthread_create(&threads[i], NULL, compute_prefix, &tasks[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < N; i++) {
        printf("product %d = %lld\n", i + 1, results[i]);
    }

    free(nums);
    free(results);
    free(threads);
    free(tasks);
    return 0;
}


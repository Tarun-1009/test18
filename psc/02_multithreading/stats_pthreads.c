/*
 * Topic 2 - Q1: Multithreaded Statistics (POSIX Threads in C)
 *
 * Usage: ./q1_stats_pthreads 90 81 78 95 79 72 85
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *nums;
    int count;
} Data;

int avg_val = 0;
int min_val = 0;
int max_val = 0;

void *calc_avg(void *arg) {
    Data *d = (Data *)arg;
    long sum = 0;
    for (int i = 0; i < d->count; i++) {
        sum += d->nums[i];
    }
    avg_val = (int)(sum / d->count);
    pthread_exit(NULL);
}

void *calc_min(void *arg) {
    Data *d = (Data *)arg;
    int m = d->nums[0];
    for (int i = 1; i < d->count; i++) {
        if (d->nums[i] < m) m = d->nums[i];
    }
    min_val = m;
    pthread_exit(NULL);
}

void *calc_max(void *arg) {
    Data *d = (Data *)arg;
    int m = d->nums[0];
    for (int i = 1; i < d->count; i++) {
        if (d->nums[i] > m) m = d->nums[i];
    }
    max_val = m;
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <num1> <num2> ...\n", argv[0]);
        return 1;
    }

    int count = argc - 1;
    int *nums = (int *)malloc((size_t)count * sizeof(int));
    for (int i = 0; i < count; i++) {
        nums[i] = atoi(argv[i + 1]);
    }

    Data data = {nums, count};
    pthread_t t_avg, t_min, t_max;

    pthread_create(&t_avg, NULL, calc_avg, &data);
    pthread_create(&t_min, NULL, calc_min, &data);
    pthread_create(&t_max, NULL, calc_max, &data);

    pthread_join(t_avg, NULL);
    pthread_join(t_min, NULL);
    pthread_join(t_max, NULL);

    printf("The average value is %d\n", avg_val);
    printf("The minimum value is %d\n", min_val);
    printf("The maximum value is %d\n", max_val);

    free(nums);
    return 0;
}


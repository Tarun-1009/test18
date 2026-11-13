#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Assignment 6 - Q1: 3 worker threads for Avg, Min, Max
int *arr, n;
double avg_val;
int min_val, max_val;

void *find_avg(void *arg) {
    double sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    avg_val = sum / n;
    pthread_exit(NULL);
}

void *find_min(void *arg) {
    min_val = arr[0];
    for (int i = 1; i < n; i++) if (arr[i] < min_val) min_val = arr[i];
    pthread_exit(NULL);
}

void *find_max(void *arg) {
    max_val = arr[0];
    for (int i = 1; i < n; i++) if (arr[i] > max_val) max_val = arr[i];
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s 90 81 78 95 79 72 85\n", argv[0]);
        return 1;
    }
    n = argc - 1;
    arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arr[i] = atoi(argv[i + 1]);

    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, find_avg, NULL);
    pthread_create(&t2, NULL, find_min, NULL);
    pthread_create(&t3, NULL, find_max, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("The average value is %.0f\n", avg_val);
    printf("The minimum value is %d\n", min_val);
    printf("The maximum value is %d\n", max_val);

    free(arr);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Assignment 6 - Q3: N threads for prefix products
int *arr;
long long *res;

void *compute(void *arg) {
    long id = (long)arg; // 1-based index
    long long p = 1;
    for (int i = 0; i < id; i++) p *= arr[i];
    res[id - 1] = p;
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s 2 3 4 5\n", argv[0]);
        return 1;
    }
    int N = argc - 1;
    arr = malloc(N * sizeof(int));
    res = malloc(N * sizeof(long long));
    pthread_t *t = malloc(N * sizeof(pthread_t));

    for (int i = 0; i < N; i++) arr[i] = atoi(argv[i + 1]);

    for (long i = 1; i <= N; i++)
        pthread_create(&t[i - 1], NULL, compute, (void *)i);

    for (int i = 0; i < N; i++) pthread_join(t[i], NULL);

    for (int i = 0; i < N; i++)
        printf("product <%d> = %lld\n", i + 1, res[i]);

    free(arr); free(res); free(t);
    return 0;
}

/*
 * N threads compute prefix products of N command-line integers.
 * Prints: product <i> = <product>
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

long long *a, *res;
int n;

void *f_prod(void *arg) {
    int id = *(int *)arg;
    long long p = 1;
    for (int j = 0; j < id; j++) p *= a[j];
    res[id - 1] = p;
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <nums...>\n", argv[0]);
        return 1;
    }
    n = argc - 1;
    a = malloc(n * sizeof(long long));
    res = malloc(n * sizeof(long long));
    pthread_t *th = malloc(n * sizeof(pthread_t));
    int *ids = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) a[i] = atoll(argv[i + 1]);

    for (int i = 0; i < n; i++) {
        ids[i] = i + 1;
        pthread_create(&th[i], NULL, f_prod, &ids[i]);
    }
    for (int i = 0; i < n; i++) pthread_join(th[i], NULL);

    for (int i = 1; i <= n; i++) {
        printf("product %d = %lld\n", i, res[i - 1]);
    }

    free(a);
    free(res);
    free(th);
    free(ids);
    return 0;
}


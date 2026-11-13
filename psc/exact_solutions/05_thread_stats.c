/*
 * 3 worker threads: average, minimum, maximum from command line integers.
 * Example: ./a.out 90 81 78 95 79 72 85
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int *a, n;
int avg_val, min_val, max_val;

void *f_avg(void *arg) {
    (void)arg;
    long s = 0;
    for (int i = 0; i < n; i++) s += a[i];
    avg_val = s / n;
    pthread_exit(NULL);
}

void *f_min(void *arg) {
    (void)arg;
    min_val = a[0];
    for (int i = 1; i < n; i++) if (a[i] < min_val) min_val = a[i];
    pthread_exit(NULL);
}

void *f_max(void *arg) {
    (void)arg;
    max_val = a[0];
    for (int i = 1; i < n; i++) if (a[i] > max_val) max_val = a[i];
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <nums...>\n", argv[0]);
        return 1;
    }
    n = argc - 1;
    a = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) a[i] = atoi(argv[i + 1]);

    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, f_avg, NULL);
    pthread_create(&t2, NULL, f_min, NULL);
    pthread_create(&t3, NULL, f_max, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("The average value is %d\n", avg_val);
    printf("The minimum value is %d\n", min_val);
    printf("The maximum value is %d\n", max_val);

    free(a);
    return 0;
}


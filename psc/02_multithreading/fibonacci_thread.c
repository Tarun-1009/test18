/*
 * Fibonacci Sequence Using a Child POSIX Thread in C
 *
 * Child thread generates n Fibonacci numbers into a shared array.
 * Parent thread waits for child and prints the sequence.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int n;
    long long *fib;
} FibData;

void *generate_fib(void *arg) {
    FibData *d = (FibData *)arg;
    if (d->n >= 1) d->fib[0] = 0;
    if (d->n >= 2) d->fib[1] = 1;
    for (int i = 2; i < d->n; i++) {
        d->fib[i] = d->fib[i - 1] + d->fib[i - 2];
    }
    return NULL;
}

int main(void) {
    int n;
    printf("Enter number of Fibonacci terms: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }

    long long *fib = (long long *)malloc((size_t)n * sizeof(long long));
    FibData data = {n, fib};

    pthread_t child;
    pthread_create(&child, NULL, generate_fib, &data);
    pthread_join(child, NULL);

    printf("Fibonacci sequence:");
    for (int i = 0; i < n; i++) {
        printf(" %lld", fib[i]);
    }
    printf("\n");

    free(fib);
    return 0;
}


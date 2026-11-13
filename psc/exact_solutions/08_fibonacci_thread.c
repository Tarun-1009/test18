/*
 * Child thread generates Fibonacci sequence in shared array.
 * Parent thread waits and displays output.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

long long *fib;
int n;

void *f_fib(void *arg) {
    (void)arg;
    if (n >= 1) fib[0] = 0;
    if (n >= 2) fib[1] = 1;
    for (int i = 2; i < n; i++) fib[i] = fib[i - 1] + fib[i - 2];
    return NULL;
}

int main(void) {
    printf("Enter number of terms: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;

    fib = malloc(n * sizeof(long long));
    pthread_t th;
    pthread_create(&th, NULL, f_fib, NULL);
    pthread_join(th, NULL);

    printf("Fibonacci sequence:");
    for (int i = 0; i < n; i++) printf(" %lld", fib[i]);
    printf("\n");

    free(fib);
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Assignment 6 - Q4: Child thread generates Fibonacci sequence
int n = 10;
long long fib[100];

void *generate(void *arg) {
    if (n >= 1) fib[0] = 0;
    if (n >= 2) fib[1] = 1;
    for (int i = 2; i < n; i++) fib[i] = fib[i - 1] + fib[i - 2];
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc > 1) n = atoi(argv[1]);

    pthread_t t;
    pthread_create(&t, NULL, generate, NULL);
    pthread_join(t, NULL);

    printf("Fibonacci sequence (%d terms):\n", n);
    for (int i = 0; i < n; i++) printf("%lld ", fib[i]);
    printf("\n");
    return 0;
}

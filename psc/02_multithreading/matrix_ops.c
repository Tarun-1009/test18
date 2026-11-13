/*
 * 40x40 Binary Matrix Operations with POSIX Threads in C
 *
 * Thread 1 computes Sum = A + B.
 * Thread 2 computes Diff = A - B.
 * Main thread waits and computes Prod = Sum * Diff.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 40

int A[N][N], B[N][N];
int Sum[N][N], Diff[N][N], Prod[N][N];

void *compute_sum(void *arg) {
    (void)arg;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            Sum[i][j] = A[i][j] + B[i][j];
        }
    }
    return NULL;
}

void *compute_diff(void *arg) {
    (void)arg;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            Diff[i][j] = A[i][j] - B[i][j];
        }
    }
    return NULL;
}

int main(void) {
    srand((unsigned int)time(NULL));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 2;
            B[i][j] = rand() % 2;
        }
    }

    pthread_t t1, t2;
    pthread_create(&t1, NULL, compute_sum, NULL);
    pthread_create(&t2, NULL, compute_diff, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            Prod[i][j] = 0;
            for (int k = 0; k < N; k++) {
                Prod[i][j] += Sum[i][k] * Diff[k][j];
            }
        }
    }

    printf("Final (A + B) * (A - B) 40x40 matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", Prod[i][j]);
        }
        printf("\n");
    }

    return 0;
}


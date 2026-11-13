/*
 * Two 40x40 binary matrices A and B.
 * Thread 1 computes Sum = A + B.
 * Thread 2 computes Diff = A - B.
 * Main computes Prod = Sum * Diff and prints result.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 40

int A[N][N], B[N][N];
int S[N][N], D[N][N], P[N][N];

void *f_sum(void *arg) {
    (void)arg;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            S[i][j] = A[i][j] + B[i][j];
    return NULL;
}

void *f_diff(void *arg) {
    (void)arg;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            D[i][j] = A[i][j] - B[i][j];
    return NULL;
}

int main(void) {
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 2;
            B[i][j] = rand() % 2;
        }
    }

    pthread_t t1, t2;
    pthread_create(&t1, NULL, f_sum, NULL);
    pthread_create(&t2, NULL, f_diff, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            P[i][j] = 0;
            for (int k = 0; k < N; k++) P[i][j] += S[i][k] * D[k][j];
            printf("%d ", P[i][j]);
        }
        printf("\n");
    }
    return 0;
}


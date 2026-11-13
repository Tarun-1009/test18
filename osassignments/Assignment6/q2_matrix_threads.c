#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 40

// Assignment 6 - Q2: Matrix addition and subtraction via threads
int A[N][N], B[N][N], Sum[N][N], Diff[N][N], Prod[N][N];

void *compute_sum(void *arg) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) Sum[i][j] = A[i][j] + B[i][j];
    pthread_exit(NULL);
}

void *compute_diff(void *arg) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) Diff[i][j] = A[i][j] - B[i][j];
    pthread_exit(NULL);
}

int main() {
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

    // Main thread multiplies Sum and Diff
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                Prod[i][j] += Sum[i][k] * Diff[k][j];

    printf("Done! Sample Prod[0][0] = %d, Prod[0][1] = %d\n", Prod[0][0], Prod[0][1]);
    return 0;
}

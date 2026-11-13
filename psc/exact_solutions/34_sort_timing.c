/*
 * Calculate execution time taken by insertion sort, selection sort, and bubble sort
 * to sort student registration numbers using functions from time.h.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void s_ins(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i], j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

void s_sel(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int m = i;
        for (int j = i + 1; j < n; j++) if (a[j] < a[m]) m = j;
        int t = a[i]; a[i] = a[m]; a[m] = t;
    }
}

void s_bub(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                int t = a[j]; a[j] = a[j + 1]; a[j + 1] = t;
            }
        }
    }
}

int main(void) {
    int n = 5000;
    int *orig = malloc(n * sizeof(int));
    int *arr  = malloc(n * sizeof(int));

    srand(time(NULL));
    for (int i = 0; i < n; i++) orig[i] = 20240000 + (rand() % 10000);

    clock_t st, en;

    memcpy(arr, orig, n * sizeof(int));
    st = clock();
    s_ins(arr, n);
    en = clock();
    printf("Insertion Sort (n=%d): %.6f sec\n", n, (double)(en - st) / CLOCKS_PER_SEC);

    memcpy(arr, orig, n * sizeof(int));
    st = clock();
    s_sel(arr, n);
    en = clock();
    printf("Selection Sort (n=%d): %.6f sec\n", n, (double)(en - st) / CLOCKS_PER_SEC);

    memcpy(arr, orig, n * sizeof(int));
    st = clock();
    s_bub(arr, n);
    en = clock();
    printf("Bubble Sort    (n=%d): %.6f sec\n", n, (double)(en - st) / CLOCKS_PER_SEC);

    free(orig);
    free(arr);
    return 0;
}


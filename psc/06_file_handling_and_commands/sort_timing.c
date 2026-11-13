/*
 * Topic 6 - Q9 (Doc Q5): Execution Time of Insertion, Selection, and Bubble Sort
 *
 * Sorts student registration numbers and measures CPU time using <time.h>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void insertion_sort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i], j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

void selection_sort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[min_idx]) min_idx = j;
        }
        int tmp = a[i]; a[i] = a[min_idx]; a[min_idx] = tmp;
    }
}

void bubble_sort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                int tmp = a[j]; a[j] = a[j + 1]; a[j + 1] = tmp;
            }
        }
    }
}

int main(void) {
    int n = 5000;
    int *orig = (int *)malloc((size_t)n * sizeof(int));
    int *arr  = (int *)malloc((size_t)n * sizeof(int));

    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++) {
        orig[i] = 20240000 + (rand() % 10000);
    }

    clock_t start, end;

    memcpy(arr, orig, (size_t)n * sizeof(int));
    start = clock();
    insertion_sort(arr, n);
    end = clock();
    printf("Insertion Sort time (n=%d): %.6f sec\n",
           n, (double)(end - start) / CLOCKS_PER_SEC);

    memcpy(arr, orig, (size_t)n * sizeof(int));
    start = clock();
    selection_sort(arr, n);
    end = clock();
    printf("Selection Sort time (n=%d): %.6f sec\n",
           n, (double)(end - start) / CLOCKS_PER_SEC);

    memcpy(arr, orig, (size_t)n * sizeof(int));
    start = clock();
    bubble_sort(arr, n);
    end = clock();
    printf("Bubble Sort time    (n=%d): %.6f sec\n",
           n, (double)(end - start) / CLOCKS_PER_SEC);

    free(orig);
    free(arr);
    return 0;
}


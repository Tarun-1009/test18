/*
 * Topic 3 - Q2: SRTF (Shortest Remaining Time First) CPU Scheduling
 *
 * Processes: A(3,4), B(1,2), C(4,1), D(2,6), E(5,2)
 */

#include <stdio.h>

#define N 5

int main(void) {
    char name[N] = {'A', 'B', 'C', 'D', 'E'};
    int at[N] = {3, 1, 4, 2, 5};
    int bt[N] = {4, 2, 1, 6, 2};
    int rem[N], ct[N] = {0};

    for (int i = 0; i < N; i++) rem[i] = bt[i];

    int completed = 0, time = 0;
    while (completed < N) {
        int best = -1;
        for (int i = 0; i < N; i++) {
            if (at[i] <= time && rem[i] > 0) {
                if (best == -1 || rem[i] < rem[best]) {
                    best = i;
                }
            }
        }
        if (best == -1) {
            time++;
            continue;
        }
        rem[best]--;
        time++;
        if (rem[best] == 0) {
            ct[best] = time;
            completed++;
        }
    }

    double sum_tat = 0, sum_wt = 0;
    printf("Proc\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < N; i++) {
        int tat = ct[i] - at[i];
        int wt = tat - bt[i];
        sum_tat += tat;
        sum_wt += wt;
        printf("%c\t%d\t%d\t%d\t%d\t%d\n", name[i], at[i], bt[i], ct[i], tat, wt);
    }
    printf("Average TAT = %.2f ms\n", sum_tat / N);
    printf("Average WT  = %.2f ms\n", sum_wt / N);
    return 0;
}


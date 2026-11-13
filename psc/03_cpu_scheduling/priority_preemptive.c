/*
 * Preemptive Priority CPU Scheduling
 *
 * Lower priority number = higher priority.
 */

#include <stdio.h>

#define N 4

int main(void) {
    char name[N][4] = {"P1", "P2", "P3", "P4"};
    int at[N]   = {0, 1, 2, 3};
    int bt[N]   = {5, 4, 2, 1};
    int prio[N] = {3, 2, 1, 4};
    int rem[N], ct[N] = {0};

    for (int i = 0; i < N; i++) rem[i] = bt[i];

    int time = 0, completed = 0;
    while (completed < N) {
        int best = -1;
        for (int i = 0; i < N; i++) {
            if (at[i] <= time && rem[i] > 0) {
                if (best == -1 || prio[i] < prio[best]) {
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
    printf("Proc\tAT\tBT\tPrio\tCT\tTAT\tWT\n");
    for (int i = 0; i < N; i++) {
        int tat = ct[i] - at[i];
        int wt = tat - bt[i];
        sum_tat += tat;
        sum_wt += wt;
        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n",
               name[i], at[i], bt[i], prio[i], ct[i], tat, wt);
    }
    printf("Average TAT = %.2f ms\n", sum_tat / N);
    printf("Average WT  = %.2f ms\n", sum_wt / N);
    return 0;
}


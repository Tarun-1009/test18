/*
 * Highest Response Ratio Next (HRRN) CPU Scheduling
 *
 * Response Ratio = (Waiting Time + Burst Time) / Burst Time.
 */

#include <stdio.h>

#define N 5

int main(void) {
    char name[N] = {'A', 'B', 'C', 'D', 'E'};
    int at[N] = {0, 2, 4, 6, 8};
    int bt[N] = {3, 6, 4, 5, 2};
    int done[N] = {0}, ct[N] = {0};

    int time = 0, completed = 0;
    while (completed < N) {
        int best = -1;
        double best_rr = -1.0;

        for (int i = 0; i < N; i++) {
            if (!done[i] && at[i] <= time) {
                int wt = time - at[i];
                double rr = (double)(wt + bt[i]) / bt[i];
                if (rr > best_rr) {
                    best_rr = rr;
                    best = i;
                }
            }
        }

        if (best == -1) {
            time++;
            continue;
        }

        time += bt[best];
        ct[best] = time;
        done[best] = 1;
        completed++;
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


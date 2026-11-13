#include <stdio.h>

// Assignment 5 - Q1(c): Round Robin Scheduling Function (tq = 2 ms)
void find_round_robin(char *p[], int at[], int bt[], int n, int tq) {
    int rem[4], ct[4], tat[4], wt[4];
    for (int i = 0; i < n; i++) rem[i] = bt[i];

    int time = 0, remain = n;
    float total_tat = 0, total_wt = 0;

    while (remain > 0) {
        int progress = 0;
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rem[i] > 0) {
                progress = 1;
                if (rem[i] > tq) {
                    time += tq;
                    rem[i] -= tq;
                } else {
                    time += rem[i];
                    rem[i] = 0;
                    ct[i] = time;
                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];
                    total_tat += tat[i];
                    total_wt += wt[i];
                    remain--;
                }
            }
        }
        if (!progress) time++;
    }

    printf("Round Robin (Time Quantum = %dms):\nProcess\tAT\tBT\tCT\tTAT\tWT\n", tq);
    for (int i = 0; i < n; i++)
        printf("%s\t%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt[i], ct[i], tat[i], wt[i]);

    printf("Avg TAT = %.2f ms, Avg WT = %.2f ms\n", total_tat / n, total_wt / n);
}

int main() {
    char *p[] = {"P1", "P2", "P3", "P4"};
    int at[] = {0, 2, 1, 3};
    int bt[] = {24, 3, 3, 7};
    int n = 4, tq = 2;

    find_round_robin(p, at, bt, n, tq); // Function call
    return 0;
}

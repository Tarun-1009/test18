#include <stdio.h>

// Assignment 5 - Q1(d): Priority Scheduling Function (P2 > P3 > P1 > P4)
void find_priority(char *p[], int at[], int bt[], int pri[], int n) {
    int done[4] = {0}, ct[4], tat[4], wt[4];
    int time = 0, count = 0;
    float total_tat = 0, total_wt = 0;

    printf("Priority Scheduling (P2 > P3 > P1 > P4):\nProcess\tAT\tBT\tPri\tCT\tTAT\tWT\n");
    while (count < n) {
        int idx = -1, best_pri = 1e9;
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && !done[i] && pri[i] < best_pri) {
                best_pri = pri[i];
                idx = i;
            }
        }
        if (idx == -1) { time++; continue; }

        time += bt[idx];
        ct[idx] = time;
        tat[idx] = ct[idx] - at[idx];
        wt[idx] = tat[idx] - bt[idx];
        total_tat += tat[idx];
        total_wt += wt[idx];
        done[idx] = 1;
        count++;

        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n", p[idx], at[idx], bt[idx], pri[idx], ct[idx], tat[idx], wt[idx]);
    }
    printf("Avg TAT = %.2f ms, Avg WT = %.2f ms\n", total_tat / n, total_wt / n);
}

int main() {
    char *p[] = {"P1", "P2", "P3", "P4"};
    int at[] = {0, 2, 1, 3};
    int bt[] = {24, 3, 3, 7};
    int pri[] = {3, 1, 2, 4}; // P2(1) > P3(2) > P1(3) > P4(4)
    int n = 4;

    find_priority(p, at, bt, pri, n); // Function call
    return 0;
}

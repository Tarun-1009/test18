#include <stdio.h>

// Assignment 5 - Q1(a): FCFS Scheduling Function
void find_fcfs(char *p[], int at[], int bt[], int n) {
    int time = 0, ct[4], tat[4], wt[4];
    float total_tat = 0, total_wt = 0;

    // Ordered by Arrival Time: P1(0), P3(1), P2(2), P4(3)
    int order[] = {0, 2, 1, 3};

    printf("FCFS Scheduling:\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        int k = order[i];
        if (time < at[k]) time = at[k];
        time += bt[k];
        ct[k] = time;
        tat[k] = ct[k] - at[k];
        wt[k] = tat[k] - bt[k];
        total_tat += tat[k];
        total_wt += wt[k];
        printf("%s\t%d\t%d\t%d\t%d\t%d\n", p[k], at[k], bt[k], ct[k], tat[k], wt[k]);
    }
    printf("Avg TAT = %.2f ms, Avg WT = %.2f ms\n", total_tat / n, total_wt / n);
}

int main() {
    char *p[] = {"P1", "P2", "P3", "P4"};
    int at[] = {0, 2, 1, 3};
    int bt[] = {24, 3, 3, 7};
    int n = 4;

    find_fcfs(p, at, bt, n); // Function call
    return 0;
}

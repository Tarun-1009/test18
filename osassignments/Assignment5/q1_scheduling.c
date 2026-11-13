#include <stdio.h>

// Assignment 5 - Q1: CPU Scheduling Algorithms using Functions
// Dataset:
// P1: AT=0, BT=24, Pri=3
// P2: AT=2, BT=3,  Pri=1 (Highest)
// P3: AT=1, BT=3,  Pri=2
// P4: AT=3, BT=7,  Pri=4 (Lowest)

void fcfs(char *p[], int at[], int bt[], int n) {
    int time = 0, ct[4], tat[4], wt[4];
    float total_tat = 0, total_wt = 0;

    // FCFS order by Arrival Time: P1(0), P3(1), P2(2), P4(3)
    int order[] = {0, 2, 1, 3}; // indices sorted by arrival time

    printf("\n--- 1(a) FCFS Scheduling ---\n");
    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");

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
    printf("Average Turnaround Time: %.2f ms\n", total_tat / n);
    printf("Average Waiting Time   : %.2f ms\n", total_wt / n);
}

void sjf(char *p[], int at[], int bt[], int n) {
    int done[4] = {0}, ct[4], tat[4], wt[4];
    int time = 0, completed = 0;
    float total_tat = 0, total_wt = 0;

    printf("\n--- 1(b) Shortest Job First (Non-preemptive) ---\n");
    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");

    while (completed < n) {
        int idx = -1, min_bt = 1e9;
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && !done[i] && bt[i] < min_bt) {
                min_bt = bt[i];
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
        completed++;
        printf("%s\t%d\t%d\t%d\t%d\t%d\n", p[idx], at[idx], bt[idx], ct[idx], tat[idx], wt[idx]);
    }
    printf("Average Turnaround Time: %.2f ms\n", total_tat / n);
    printf("Average Waiting Time   : %.2f ms\n", total_wt / n);
}

void round_robin(char *p[], int at[], int bt[], int n, int tq) {
    int rem[4], ct[4], tat[4], wt[4];
    for (int i = 0; i < n; i++) rem[i] = bt[i];
    int time = 0, completed = 0;
    float total_tat = 0, total_wt = 0;

    printf("\n--- 1(c) Round Robin (Time Quantum = %d ms) ---\n", tq);

    while (completed < n) {
        int active = 0;
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rem[i] > 0) {
                active = 1;
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
                    completed++;
                }
            }
        }
        if (!active) time++;
    }

    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    printf("Average Turnaround Time: %.2f ms\n", total_tat / n);
    printf("Average Waiting Time   : %.2f ms\n", total_wt / n);
}

void priority_scheduling(char *p[], int at[], int bt[], int pri[], int n) {
    int done[4] = {0}, ct[4], tat[4], wt[4];
    int time = 0, completed = 0;
    float total_tat = 0, total_wt = 0;

    printf("\n--- 1(d) Priority Scheduling (P2 > P3 > P1 > P4) ---\n");
    printf("Process\tAT\tBT\tPri\tCT\tTAT\tWT\n");

    while (completed < n) {
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
        completed++;
        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n", p[idx], at[idx], bt[idx], pri[idx], ct[idx], tat[idx], wt[idx]);
    }
    printf("Average Turnaround Time: %.2f ms\n", total_tat / n);
    printf("Average Waiting Time   : %.2f ms\n", total_wt / n);
}

int main() {
    char *p[] = {"P1", "P2", "P3", "P4"};
    int at[] = {0, 2, 1, 3};
    int bt[] = {24, 3, 3, 7};
    int pri[] = {3, 1, 2, 4}; // Priority: P2(1) > P3(2) > P1(3) > P4(4)
    int n = 4;

    printf("============================================================\n");
    printf("         CPU SCHEDULING ALGORITHMS (FUNCTION CALLS)         \n");
    printf("============================================================\n");

    // Calling each algorithm as a function
    fcfs(p, at, bt, n);
    sjf(p, at, bt, n);
    round_robin(p, at, bt, n, 2);
    priority_scheduling(p, at, bt, pri, n);

    return 0;
}

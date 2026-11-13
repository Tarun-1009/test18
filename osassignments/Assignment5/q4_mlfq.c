#include <stdio.h>

// Assignment 5 - Q4: Multi-Level Feedback Queue (MLFQ) Function
// Q1: RR (tq = 3 ms), Q2: FCFS (Preempted by Q1)
void find_mlfq(char *p[], int at[], int bt[], int n) {
    int rem[5], ct[5], tat[5], wt[5];
    int q1_used[] = {0, 0, 0, 0, 0};
    for (int i = 0; i < n; i++) rem[i] = bt[i];

    int time = 0, count = 0;
    float total_tat = 0, total_wt = 0;

    printf("Gantt Chart Timeline: ");
    while (count < n) {
        int idx = -1;

        // 1. Queue 1: Ready and hasn't used up 3 ms yet
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rem[i] > 0 && q1_used[i] < 3) {
                idx = i;
                break;
            }
        }

        // 2. Queue 2 (FCFS): If no process in Q1
        if (idx == -1) {
            for (int i = 0; i < n; i++) {
                if (at[i] <= time && rem[i] > 0) {
                    idx = i;
                    break;
                }
            }
        }

        if (idx == -1) { time++; continue; }

        printf("[%d: %s] ", time, p[idx]);
        rem[idx]--;
        q1_used[idx]++;
        time++;

        if (rem[idx] == 0) {
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            total_tat += tat[idx];
            total_wt += wt[idx];
            count++;
        }
    }
    printf("[%d: END]\n\n", time);

    printf("MLFQ Results:\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("%s\t%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt[i], ct[i], tat[i], wt[i]);

    printf("Avg TAT = %.2f ms, Avg WT = %.2f ms\n", total_tat / n, total_wt / n);
}

int main() {
    char *p[] = {"P1", "P2", "P3", "P4", "P5"};
    int at[] = {0, 1, 2, 4, 6};
    int bt[] = {8, 4, 6, 3, 5};
    int n = 5;

    find_mlfq(p, at, bt, n); // Function call
    return 0;
}

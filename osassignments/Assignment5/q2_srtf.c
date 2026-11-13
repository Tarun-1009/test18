#include <stdio.h>

// Assignment 5 - Q2: Shortest Remaining Time First (SRTF) Function
void find_srtf(char *p[], int at[], int bt[], int n) {
    int rem[5], ct[5], tat[5], wt[5];
    for (int i = 0; i < n; i++) rem[i] = bt[i];

    int count = 0, time = 0;
    float total_tat = 0, total_wt = 0;

    while (count < n) {
        int idx = -1, min_rem = 1e9;
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rem[i] > 0 && rem[i] < min_rem) {
                min_rem = rem[i];
                idx = i;
            }
        }
        if (idx == -1) { time++; continue; }

        rem[idx]--;
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

    printf("SRTF Scheduling:\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("%s\t%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt[i], ct[i], tat[i], wt[i]);

    printf("Avg TAT = %.2f ms, Avg WT = %.2f ms\n", total_tat / n, total_wt / n);
}

int main() {
    char *p[] = {"A", "B", "C", "D", "E"};
    int at[] = {3, 1, 4, 2, 5};
    int bt[] = {4, 2, 1, 6, 2};
    int n = 5;

    find_srtf(p, at, bt, n); // Function call
    return 0;
}

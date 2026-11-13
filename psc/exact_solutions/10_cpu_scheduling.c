/*
 * CPU Scheduling: FCFS, SJF, RR (t=2), Priority (P2 > P3 > P1 > P4)
 * Problem data:
 *   P1: AT=0, BT=24
 *   P2: AT=2, BT=3
 *   P3: AT=1, BT=3
 *   P4: AT=3, BT=7
 */

#include <stdio.h>

#define N 4

int at[N] = {0, 2, 1, 3};
int bt[N] = {24, 3, 3, 7};
int pr[N] = {3, 1, 2, 4}; /* P2 > P3 > P1 > P4 */

void print_res(const char *name, int ct[]) {
    float s_tat = 0, s_wt = 0;
    printf("\n--- %s ---\n", name);
    printf("Proc\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < N; i++) {
        int tat = ct[i] - at[i];
        int wt = tat - bt[i];
        s_tat += tat;
        s_wt += wt;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat, wt);
    }
    printf("Average TAT = %.2f ms\n", s_tat / N);
    printf("Average WT  = %.2f ms\n", s_wt / N);
}

void fcfs(void) {
    int idx[N] = {0, 1, 2, 3};
    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            if (at[idx[j]] < at[idx[i]]) {
                int t = idx[i]; idx[i] = idx[j]; idx[j] = t;
            }
        }
    }
    int ct[N], cur = 0;
    for (int k = 0; k < N; k++) {
        int i = idx[k];
        if (cur < at[i]) cur = at[i];
        cur += bt[i];
        ct[i] = cur;
    }
    print_res("FCFS", ct);
}

void sjf(void) {
    int done[N] = {0}, ct[N], fin = 0, cur = 0;
    while (fin < N) {
        int b = -1;
        for (int i = 0; i < N; i++) {
            if (!done[i] && at[i] <= cur) {
                if (b == -1 || bt[i] < bt[b]) b = i;
            }
        }
        if (b == -1) { cur++; continue; }
        cur += bt[b];
        ct[b] = cur;
        done[b] = 1;
        fin++;
    }
    print_res("SJF (Non-Preemptive)", ct);
}

void rr(int q) {
    int rem[N], ct[N], in_q[N] = {0}, queue[100], f = 0, r = 0;
    for (int i = 0; i < N; i++) rem[i] = bt[i];

    int cur = 0, fin = 0;
    while (fin < N) {
        for (int i = 0; i < N; i++) {
            if (!in_q[i] && rem[i] > 0 && at[i] <= cur) {
                queue[r++] = i;
                in_q[i] = 1;
            }
        }
        if (f == r) { cur++; continue; }

        int i = queue[f++];
        int slice = (rem[i] < q) ? rem[i] : q;
        rem[i] -= slice;
        cur += slice;

        for (int j = 0; j < N; j++) {
            if (!in_q[j] && rem[j] > 0 && at[j] <= cur) {
                queue[r++] = j;
                in_q[j] = 1;
            }
        }
        if (rem[i] > 0) queue[r++] = i;
        else { ct[i] = cur; fin++; }
    }
    print_res("Round Robin (t = 2 ms)", ct);
}

void priority(void) {
    int done[N] = {0}, ct[N], fin = 0, cur = 0;
    while (fin < N) {
        int b = -1;
        for (int i = 0; i < N; i++) {
            if (!done[i] && at[i] <= cur) {
                if (b == -1 || pr[i] < pr[b]) b = i;
            }
        }
        if (b == -1) { cur++; continue; }
        cur += bt[b];
        ct[b] = cur;
        done[b] = 1;
        fin++;
    }
    print_res("Priority (P2 > P3 > P1 > P4)", ct);
}

int main(void) {
    fcfs();
    sjf();
    rr(2);
    priority();
    return 0;
}


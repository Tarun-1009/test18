/*
 * Topic 3 - Q1: CPU Scheduling Algorithms (FCFS, SJF, Round Robin, Priority)
 *
 * Processes:
 *   P1: AT=0, BT=24, Priority=3
 *   P2: AT=2, BT=3,  Priority=1 (highest: P2 > P3 > P1 > P4)
 *   P3: AT=1, BT=3,  Priority=2
 *   P4: AT=3, BT=7,  Priority=4
 * Time slice for RR = 2 ms.
 */

#include <stdio.h>

#define N 4

typedef struct {
    char name[4];
    int at;
    int bt;
    int prio; /* smaller number = higher priority */
} Process;

static const Process BASE[N] = {
    {"P1", 0, 24, 3},
    {"P2", 2,  3, 1},
    {"P3", 1,  3, 2},
    {"P4", 3,  7, 4}
};

void print_table(const char *title, int ct[], int tat[], int wt[]) {
    double sum_tat = 0, sum_wt = 0;
    printf("\n=== %s ===\n", title);
    printf("Proc\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < N; i++) {
        tat[i] = ct[i] - BASE[i].at;
        wt[i] = tat[i] - BASE[i].bt;
        sum_tat += tat[i];
        sum_wt += wt[i];
        printf("%s\t%d\t%d\t%d\t%d\t%d\n",
               BASE[i].name, BASE[i].at, BASE[i].bt, ct[i], tat[i], wt[i]);
    }
    printf("Average TAT = %.2f ms, Average WT = %.2f ms\n",
           sum_tat / N, sum_wt / N);
}

void run_fcfs(void) {
    int order[N] = {0, 1, 2, 3};
    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            if (BASE[order[j]].at < BASE[order[i]].at) {
                int tmp = order[i]; order[i] = order[j]; order[j] = tmp;
            }
        }
    }
    int ct[N], tat[N], wt[N], time = 0;
    for (int k = 0; k < N; k++) {
        int i = order[k];
        if (time < BASE[i].at) time = BASE[i].at;
        time += BASE[i].bt;
        ct[i] = time;
    }
    print_table("FCFS Scheduling", ct, tat, wt);
}

void run_sjf(void) {
    int done[N] = {0}, ct[N], tat[N], wt[N];
    int completed = 0, time = 0;
    while (completed < N) {
        int best = -1;
        for (int i = 0; i < N; i++) {
            if (!done[i] && BASE[i].at <= time) {
                if (best == -1 || BASE[i].bt < BASE[best].bt) best = i;
            }
        }
        if (best == -1) { time++; continue; }
        time += BASE[best].bt;
        ct[best] = time;
        done[best] = 1;
        completed++;
    }
    print_table("SJF Scheduling (Non-Preemptive)", ct, tat, wt);
}

void run_rr(int quantum) {
    int rem[N], ct[N], tat[N], wt[N], in_q[N] = {0};
    int queue[100], front = 0, rear = 0;
    for (int i = 0; i < N; i++) rem[i] = BASE[i].bt;

    int time = 0, completed = 0;
    while (completed < N) {
        for (int i = 0; i < N; i++) {
            if (!in_q[i] && rem[i] > 0 && BASE[i].at <= time) {
                queue[rear++] = i;
                in_q[i] = 1;
            }
        }
        if (front == rear) { time++; continue; }

        int cur = queue[front++];
        int slice = (rem[cur] < quantum) ? rem[cur] : quantum;
        rem[cur] -= slice;
        time += slice;

        for (int i = 0; i < N; i++) {
            if (!in_q[i] && rem[i] > 0 && BASE[i].at <= time) {
                queue[rear++] = i;
                in_q[i] = 1;
            }
        }
        if (rem[cur] > 0) {
            queue[rear++] = cur;
        } else {
            ct[cur] = time;
            completed++;
        }
    }
    print_table("Round Robin Scheduling (t = 2 ms)", ct, tat, wt);
}

void run_priority(void) {
    int done[N] = {0}, ct[N], tat[N], wt[N];
    int completed = 0, time = 0;
    while (completed < N) {
        int best = -1;
        for (int i = 0; i < N; i++) {
            if (!done[i] && BASE[i].at <= time) {
                if (best == -1 || BASE[i].prio < BASE[best].prio) best = i;
            }
        }
        if (best == -1) { time++; continue; }
        time += BASE[best].bt;
        ct[best] = time;
        done[best] = 1;
        completed++;
    }
    print_table("Priority Scheduling (P2 > P3 > P1 > P4)", ct, tat, wt);
}

int main(void) {
    run_fcfs();
    run_sjf();
    run_rr(2);
    run_priority();
    return 0;
}


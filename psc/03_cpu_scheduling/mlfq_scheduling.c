/*
 * Topic 3 - Q4: Multilevel Feedback Queue (MLFQ) Scheduling
 *
 * Queue 1 (High): Round Robin (quantum = 3 ms)
 * Queue 2 (Low):  FCFS
 * Newly arrived process enters Queue 1. If not finished within 3 ms, moves to Queue 2.
 * CPU always selects Queue 1 when non-empty.
 */

#include <stdio.h>

#define N 5
#define QUANTUM 3

typedef struct {
    char name[4];
    int at;
    int bt;
    int rem;
    int ct;
    int in_q; /* 0 = not arrived, 1 = in Q1/Q2, 2 = done */
} Process;

int main(void) {
    Process p[N] = {
        {"P1", 0, 8, 8, 0, 0},
        {"P2", 1, 4, 4, 0, 0},
        {"P3", 2, 6, 6, 0, 0},
        {"P4", 4, 3, 3, 0, 0},
        {"P5", 6, 5, 5, 0, 0}
    };

    int q1[50], f1 = 0, r1 = 0;
    int q2[50], f2 = 0, r2 = 0;
    int time = 0, completed = 0;

    printf("Gantt Chart:\n");
    while (completed < N) {
        for (int i = 0; i < N; i++) {
            if (p[i].in_q == 0 && p[i].at <= time) {
                q1[r1++] = i;
                p[i].in_q = 1;
            }
        }

        if (f1 < r1) {
            int idx = q1[f1++];
            int run = (p[idx].rem < QUANTUM) ? p[idx].rem : QUANTUM;
            int start = time;
            time += run;
            p[idx].rem -= run;
            printf("| %s (%d-%d) ", p[idx].name, start, time);

            for (int i = 0; i < N; i++) {
                if (p[i].in_q == 0 && p[i].at <= time) {
                    q1[r1++] = i;
                    p[i].in_q = 1;
                }
            }
            if (p[idx].rem == 0) {
                p[idx].ct = time;
                p[idx].in_q = 2;
                completed++;
            } else {
                q2[r2++] = idx;
            }
        } else if (f2 < r2) {
            int idx = q2[f2++];
            int start = time;
            /* Run 1 ms at a time or until Q1 gets a new arrival */
            while (p[idx].rem > 0) {
                p[idx].rem--;
                time++;
                int preempt = 0;
                for (int i = 0; i < N; i++) {
                    if (p[i].in_q == 0 && p[i].at <= time) {
                        q1[r1++] = i;
                        p[i].in_q = 1;
                        preempt = 1;
                    }
                }
                if (preempt && p[idx].rem > 0) {
                    q2[r2++] = idx;
                    break;
                }
            }
            printf("| %s (%d-%d) ", p[idx].name, start, time);
            if (p[idx].rem == 0) {
                p[idx].ct = time;
                p[idx].in_q = 2;
                completed++;
            }
        } else {
            time++;
        }
    }
    printf("|\n\n");

    double sum_tat = 0, sum_wt = 0;
    printf("Proc\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < N; i++) {
        int tat = p[i].ct - p[i].at;
        int wt = tat - p[i].bt;
        sum_tat += tat;
        sum_wt += wt;
        printf("%s\t%d\t%d\t%d\t%d\t%d\n",
               p[i].name, p[i].at, p[i].bt, p[i].ct, tat, wt);
    }
    printf("Average TAT = %.2f ms\n", sum_tat / N);
    printf("Average WT  = %.2f ms\n", sum_wt / N);
    return 0;
}


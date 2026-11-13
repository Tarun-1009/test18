/*
 * Multilevel Feedback Queue (MLFQ):
 * Queue 1: RR (quantum = 3)
 * Queue 2: FCFS
 * Queue 1 has higher priority than Queue 2.
 * Processes:
 *   P1: AT 0, BT 8
 *   P2: AT 1, BT 4
 *   P3: AT 2, BT 6
 *   P4: AT 4, BT 3
 *   P5: AT 6, BT 5
 */

#include <stdio.h>

#define N 5
#define Q 3

typedef struct {
    char name[4];
    int at, bt, rem, ct, st;
} Proc;

int main(void) {
    Proc p[N] = {
        {"P1", 0, 8, 8, 0, 0},
        {"P2", 1, 4, 4, 0, 0},
        {"P3", 2, 6, 6, 0, 0},
        {"P4", 4, 3, 3, 0, 0},
        {"P5", 6, 5, 5, 0, 0}
    };

    int q1[100], f1 = 0, r1 = 0;
    int q2[100], f2 = 0, r2 = 0;
    int cur = 0, fin = 0;

    printf("Gantt Chart:\n");
    while (fin < N) {
        for (int i = 0; i < N; i++) {
            if (p[i].st == 0 && p[i].at <= cur) {
                q1[r1++] = i;
                p[i].st = 1;
            }
        }

        if (f1 < r1) {
            int i = q1[f1++];
            int run = (p[i].rem < Q) ? p[i].rem : Q;
            int start = cur;
            cur += run;
            p[i].rem -= run;
            printf("| %s (%d-%d) ", p[i].name, start, cur);

            for (int j = 0; j < N; j++) {
                if (p[j].st == 0 && p[j].at <= cur) {
                    q1[r1++] = j;
                    p[j].st = 1;
                }
            }
            if (p[i].rem == 0) {
                p[i].ct = cur;
                p[i].st = 2;
                fin++;
            } else {
                q2[r2++] = i;
            }
        } else if (f2 < r2) {
            int i = q2[f2++];
            int start = cur;
            while (p[i].rem > 0) {
                p[i].rem--;
                cur++;
                int prem = 0;
                for (int j = 0; j < N; j++) {
                    if (p[j].st == 0 && p[j].at <= cur) {
                        q1[r1++] = j;
                        p[j].st = 1;
                        prem = 1;
                    }
                }
                if (prem && p[i].rem > 0) {
                    q2[r2++] = i;
                    break;
                }
            }
            printf("| %s (%d-%d) ", p[i].name, start, cur);
            if (p[i].rem == 0) {
                p[i].ct = cur;
                p[i].st = 2;
                fin++;
            }
        } else {
            cur++;
        }
    }
    printf("|\n\n");

    float s_tat = 0, s_wt = 0;
    printf("Proc\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < N; i++) {
        int tat = p[i].ct - p[i].at;
        int wt = tat - p[i].bt;
        s_tat += tat;
        s_wt += wt;
        printf("%s\t%d\t%d\t%d\t%d\t%d\n", p[i].name, p[i].at, p[i].bt, p[i].ct, tat, wt);
    }
    printf("Average TAT = %.2f ms\n", s_tat / N);
    printf("Average WT  = %.2f ms\n", s_wt / N);
    return 0;
}


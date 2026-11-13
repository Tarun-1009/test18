/*
 * Topic 3 - Q3: Multi-Level Queue (MLQ) Scheduling
 *
 * Queue 1 (High): System Processes (fixed priority 1..3)
 * Queue 2 (Low):  User Processes (fixed priority 1..3)
 * Processes: P1(3, User), P2(2, System), P3(5, User), P4(1, System)
 */

#include <stdio.h>

typedef struct {
    char name[4];
    int bt;
    int is_system; /* 1 = System, 0 = User */
    int priority;  /* 1 (highest) to 3 (lowest) */
} Process;

int main(void) {
    Process procs[] = {
        {"P1", 3, 0, 2},
        {"P2", 2, 1, 2},
        {"P3", 5, 0, 1},
        {"P4", 1, 1, 1}
    };
    int n = 4;

    /* Sort by: System before User, then higher priority (smaller number) */
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            int swap = 0;
            if (procs[j].is_system > procs[i].is_system) {
                swap = 1;
            } else if (procs[j].is_system == procs[i].is_system &&
                       procs[j].priority < procs[i].priority) {
                swap = 1;
            }
            if (swap) {
                Process tmp = procs[i];
                procs[i] = procs[j];
                procs[j] = tmp;
            }
        }
    }

    int time = 0;
    double sum_tat = 0, sum_wt = 0;
    printf("Proc\tType\tPrio\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        int wt = time;
        time += procs[i].bt;
        int ct = time;
        int tat = ct; /* AT = 0 */
        sum_tat += tat;
        sum_wt += wt;
        printf("%s\t%s\t%d\t%d\t%d\t%d\t%d\n",
               procs[i].name,
               procs[i].is_system ? "System" : "User",
               procs[i].priority,
               procs[i].bt, ct, tat, wt);
    }
    printf("Average TAT = %.2f ms\n", sum_tat / n);
    printf("Average WT  = %.2f ms\n", sum_wt / n);
    return 0;
}


/*
 * Multilevel Queue Scheduling:
 * System processes have higher priority than User processes.
 * Priority 1 to 3 (1 is highest). Fixed priority scheduling.
 * Scenario:
 *   P1: BT 3, User, Prio 2
 *   P2: BT 2, System, Prio 2
 *   P3: BT 5, User, Prio 1
 *   P4: BT 1, System, Prio 1
 */

#include <stdio.h>

typedef struct {
    char name[4];
    int bt;
    int sys;  /* 1: System, 0: User */
    int prio; /* 1: highest */
} Proc;

int main(void) {
    Proc p[4] = {
        {"P1", 3, 0, 2},
        {"P2", 2, 1, 2},
        {"P3", 5, 0, 1},
        {"P4", 1, 1, 1}
    };
    int n = 4;

    /* Sort by: System > User, then lower prio number */
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            int swap = 0;
            if (p[j].sys > p[i].sys) swap = 1;
            else if (p[j].sys == p[i].sys && p[j].prio < p[i].prio) swap = 1;

            if (swap) {
                Proc t = p[i]; p[i] = p[j]; p[j] = t;
            }
        }
    }

    int cur = 0;
    float s_tat = 0, s_wt = 0;
    printf("Proc\tType\tPrio\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        int wt = cur;
        cur += p[i].bt;
        int ct = cur;
        int tat = ct; /* AT = 0 */
        s_tat += tat;
        s_wt += wt;
        printf("%s\t%s\t%d\t%d\t%d\t%d\t%d\n",
               p[i].name, p[i].sys ? "System" : "User", p[i].prio, p[i].bt, ct, tat, wt);
    }
    printf("Average TAT = %.2f ms\n", s_tat / n);
    printf("Average WT  = %.2f ms\n", s_wt / n);
    return 0;
}


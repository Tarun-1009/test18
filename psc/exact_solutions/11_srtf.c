/*
 * SRTF CPU scheduling simulation.
 * Scenario:
 *   A: AT 3, BT 4
 *   B: AT 1, BT 2
 *   C: AT 4, BT 1
 *   D: AT 2, BT 6
 *   E: AT 5, BT 2
 */

#include <stdio.h>

#define N 5

int main(void) {
    char name[N] = {'A', 'B', 'C', 'D', 'E'};
    int at[N] = {3, 1, 4, 2, 5};
    int bt[N] = {4, 2, 1, 6, 2};
    int rem[N], ct[N] = {0};

    for (int i = 0; i < N; i++) rem[i] = bt[i];

    int fin = 0, cur = 0;
    while (fin < N) {
        int b = -1;
        for (int i = 0; i < N; i++) {
            if (at[i] <= cur && rem[i] > 0) {
                if (b == -1 || rem[i] < rem[b]) b = i;
            }
        }
        if (b == -1) { cur++; continue; }

        rem[b]--;
        cur++;
        if (rem[b] == 0) {
            ct[b] = cur;
            fin++;
        }
    }

    float s_tat = 0, s_wt = 0;
    printf("Proc\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < N; i++) {
        int tat = ct[i] - at[i];
        int wt = tat - bt[i];
        s_tat += tat;
        s_wt += wt;
        printf("%c\t%d\t%d\t%d\t%d\t%d\n", name[i], at[i], bt[i], ct[i], tat, wt);
    }
    printf("Average TAT = %.2f ms\n", s_tat / N);
    printf("Average WT  = %.2f ms\n", s_wt / N);
    return 0;
}


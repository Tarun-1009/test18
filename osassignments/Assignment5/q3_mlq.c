#include <stdio.h>

// Assignment 5 - Q3: Multi-Level Queue Scheduling Function
void find_mlq(char *p[], char *type[], int bt[], int n) {
    int time = 0;
    float total_tat = 0, total_wt = 0;

    printf("Multi-Level Queue Scheduling (System > User):\n");
    printf("Process\tType\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        int wt = time;
        time += bt[i];
        int ct = time;
        int tat = ct; // Arrival time = 0
        total_tat += tat;
        total_wt += wt;
        printf("%s\t%s\t%d\t%d\t%d\t%d\n", p[i], type[i], bt[i], ct, tat, wt);
    }

    printf("Avg TAT = %.2f ms, Avg WT = %.2f ms\n", total_tat / n, total_wt / n);
}

int main() {
    // System processes (P2, P4) scheduled before User processes (P1, P3)
    char *p[] = {"P2", "P4", "P1", "P3"};
    char *type[] = {"System", "System", "User", "User"};
    int bt[] = {2, 1, 3, 5};
    int n = 4;

    find_mlq(p, type, bt, n); // Function call
    return 0;
}

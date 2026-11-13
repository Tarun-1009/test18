/*
 * Adjusted sleep:
 * Child A sleeps 100ms, Child B sleeps 10ms.
 *
 * Prediction:
 * Child B finishes all 5 iterations (1000 -> 1500) while Child A is still sleeping.
 * Child A then overwrites 1000 + 200 = 1200, then adds 200 x 4 = 2000.
 * So final output becomes 2000. Still not 100% guaranteed on pre-empting OS scheduler.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    int *x = (int *)shmat(id, NULL, 0);
    *x = 1000;
    printf("Initial: %d\n", *x);

    if (fork() == 0) {
        for (int i = 0; i < 5; i++) {
            int t = *x;
            usleep(100000); /* 100ms */
            *x = t + 200;
            printf("Child A: %d\n", *x);
        }
        shmdt(x);
        exit(0);
    }

    if (fork() == 0) {
        for (int i = 0; i < 5; i++) {
            int t = *x;
            usleep(10000); /* 10ms */
            *x = t + 100;
            printf("Child B: %d\n", *x);
        }
        shmdt(x);
        exit(0);
    }

    wait(NULL);
    wait(NULL);
    printf("Final output: %d\n", *x);

    shmdt(x);
    shmctl(id, IPC_RMID, NULL);
    return 0;
}


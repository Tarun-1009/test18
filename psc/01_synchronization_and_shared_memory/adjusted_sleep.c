/*
 * Topic 1 - Q1(b): Adjusted Sleep Duration in Shared Memory Race Condition
 *
 * By making Child A sleep longer (150 ms) and Child B sleep shorter (10 ms),
 * Child B finishes all 5 updates (+500 -> 1500) before Child A's first write,
 * and Child A overwrites with 1000 + 200 = 1200, then continues to 2000.
 *
 * Prediction:
 *   If Child A reads 1000 first, sleeps 150 ms while Child B completes all 5
 *   iterations (1000 -> 1500), Child A then writes 1200 and runs 4 more
 *   iterations (+800), producing 2000. Still not strictly guaranteed on a busy OS
 *   scheduler, because process scheduling is non-deterministic.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        return 1;
    }

    int *shared_var = (int *)shmat(shmid, NULL, 0);
    if (shared_var == (void *)-1) {
        perror("shmat");
        return 1;
    }

    *shared_var = 1000;
    printf("Parent initialized shared_var = %d\n", *shared_var);

    if (fork() == 0) {
        for (int i = 0; i < 5; i++) {
            int temp = *shared_var;
            usleep(150000); /* 150 ms */
            *shared_var = temp + 200;
            printf("Child A (iter %d): wrote %d\n", i + 1, *shared_var);
        }
        shmdt(shared_var);
        exit(0);
    }

    if (fork() == 0) {
        for (int i = 0; i < 5; i++) {
            int temp = *shared_var;
            usleep(10000); /* 10 ms */
            *shared_var = temp + 100;
            printf("Child B (iter %d): wrote %d\n", i + 1, *shared_var);
        }
        shmdt(shared_var);
        exit(0);
    }

    wait(NULL);
    wait(NULL);

    printf("Final shared_var = %d\n", *shared_var);

    shmdt(shared_var);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}


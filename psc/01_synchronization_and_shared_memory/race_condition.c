/*
 * Topic 1 - Q1(a): Shared Memory Race Condition
 *
 * Parent creates shared memory, initializes value to 1000, forks Child A (+200 x 5)
 * and Child B (+100 x 5). Both sleep randomly between reading and writing back
 * to trigger a race condition.
 *
 * Prediction before execution:
 *   The final value CANNOT be predicted deterministically.
 *   Ideally: 1000 + (5 * 200) + (5 * 100) = 2500.
 *   Because both processes read the same value before either writes back
 *   (lost update), the final value will usually be less than 2500 and vary
 *   across runs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>
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
        srand((unsigned int)(time(NULL) ^ getpid()));
        for (int i = 0; i < 5; i++) {
            int temp = *shared_var;
            usleep((rand() % 5 + 1) * 10000);
            *shared_var = temp + 200;
            printf("Child A (iter %d): wrote %d\n", i + 1, *shared_var);
        }
        shmdt(shared_var);
        exit(0);
    }

    if (fork() == 0) {
        srand((unsigned int)(time(NULL) ^ getpid()));
        for (int i = 0; i < 5; i++) {
            int temp = *shared_var;
            usleep((rand() % 5 + 1) * 10000);
            *shared_var = temp + 100;
            printf("Child B (iter %d): wrote %d\n", i + 1, *shared_var);
        }
        shmdt(shared_var);
        exit(0);
    }

    wait(NULL);
    wait(NULL);

    printf("Final shared_var = %d (expected without race: 2500)\n", *shared_var);

    shmdt(shared_var);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}


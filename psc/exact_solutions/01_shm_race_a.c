/*
 * Parent creates shared memory, writes 1000.
 * Two children A and B do 5 iterations.
 * Child A: +200 each iter.
 * Child B: +100 each iter.
 * Random sleep between read and write to trigger race condition.
 *
 * Prediction:
 * Final value cannot be predicted deterministically before execution.
 * Without race: 1000 + 5*200 + 5*100 = 2500.
 * With race: updates get lost, so final value is usually < 2500 and varies.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(void) {
    int id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    int *x = (int *)shmat(id, NULL, 0);
    *x = 1000;
    printf("Initial: %d\n", *x);

    if (fork() == 0) {
        srand(getpid());
        for (int i = 0; i < 5; i++) {
            int t = *x;
            usleep((rand() % 5 + 1) * 10000);
            *x = t + 200;
            printf("Child A: %d\n", *x);
        }
        shmdt(x);
        exit(0);
    }

    if (fork() == 0) {
        srand(getpid());
        for (int i = 0; i < 5; i++) {
            int t = *x;
            usleep((rand() % 5 + 1) * 10000);
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


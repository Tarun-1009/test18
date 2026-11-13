#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>

// Assignment 8 - Q1: Shared Memory Race Condition
// Child A adds 200 (5 times), Child B adds 100 (5 times)
int main() {
    int shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    int *val = (int *)shmat(shmid, NULL, 0);
    *val = 1000;

    if (fork() == 0) {
        // Child A
        for (int i = 0; i < 5; i++) {
            int temp = *val;
            usleep(rand() % 50000); // Random delay creates race condition
            *val = temp + 200;
        }
        exit(0);
    }

    if (fork() == 0) {
        // Child B
        for (int i = 0; i < 5; i++) {
            int temp = *val;
            usleep(rand() % 50000); // Random delay creates race condition
            *val = temp + 100;
        }
        exit(0);
    }

    wait(NULL);
    wait(NULL);
    printf("Expected: 2500 | Actual value with race condition: %d\n", *val);

    shmdt(val);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}

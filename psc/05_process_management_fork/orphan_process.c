/*
 * Orphan Process Demonstration
 *
 * Parent exits immediately; child sleeps briefly and gets adopted by PID 1.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid > 0) {
        printf("Parent (PID %d) exiting before child (PID %d).\n", getpid(), pid);
        exit(0);
    } else {
        printf("Child (PID %d) initial PPID = %d\n", getpid(), getppid());
        sleep(1);
        printf("Child (PID %d) after parent exit, new PPID = %d\n",
               getpid(), getppid());
    }
    return 0;
}


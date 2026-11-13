/*
 * Zombie Process Demonstration
 *
 * Child exits immediately while parent sleeps before calling wait().
 * During that window, the child remains in zombie (Z) state.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        printf("Child (PID %d) exiting now (becomes zombie until waited).\n",
               getpid());
        exit(0);
    } else {
        sleep(2);
        wait(NULL);
        printf("Parent reaped child (PID %d).\n", pid);
    }
    return 0;
}


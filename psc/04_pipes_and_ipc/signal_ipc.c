/*
 * Inter-Process Communication Using Signals (SIGUSR1)
 *
 * Child sends SIGUSR1 to Parent; Parent catches it with a signal handler.
 */

#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

static volatile sig_atomic_t got_signal = 0;

void handle_sigusr1(int sig) {
    (void)sig;
    got_signal = 1;
}

int main(void) {
    signal(SIGUSR1, handle_sigusr1);

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        usleep(100000);
        printf("Child (PID %d) sending SIGUSR1 to Parent (PID %d)\n",
               getpid(), getppid());
        kill(getppid(), SIGUSR1);
    } else {
        while (!got_signal) {
            pause();
        }
        printf("Parent (PID %d) received SIGUSR1!\n", getpid());
        wait(NULL);
    }
    return 0;
}


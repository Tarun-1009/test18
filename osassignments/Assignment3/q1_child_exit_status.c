#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Assignment 3 - Q1: Wait for child, print PID & termination state
int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child Process (PID: %d) exiting...\n", getpid());
        exit(10); // status 10
    } else {
        int status;
        pid_t child_pid = wait(&status);
        int exit_code = WEXITSTATUS(status);
        printf("Child PID: %d terminated.\n", child_pid);
        printf("Termination status (Decimal): %d\n", exit_code);
        printf("Termination status (Hex)    : 0x%X\n", exit_code);
    }
    return 0;
}

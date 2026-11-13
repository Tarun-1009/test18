/*
 * Topic 5 - Q1: Child PID and Termination Status (Decimal & Hexadecimal)
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
        printf("Child process running (PID = %d)\n", getpid());
        exit(42);
    } else {
        int status;
        pid_t ended = wait(&status);
        printf("Parent: Child PID = %d terminated\n", ended);
        printf("Raw wait status: decimal = %d, hex = 0x%x\n", status, status);
        if (WIFEXITED(status)) {
            int code = WEXITSTATUS(status);
            printf("Exit code: decimal = %d, hex = 0x%x\n", code, code);
        }
    }
    return 0;
}


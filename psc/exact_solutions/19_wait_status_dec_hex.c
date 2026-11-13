/*
 * Creates child process, waits for child termination.
 * Prints child PID and termination state in decimal and hexadecimal.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child process running with PID = %d\n", getpid());
        exit(15);
    } else {
        int st;
        pid_t c = wait(&st);
        printf("Terminated Child PID: %d\n", c);
        printf("Termination Status: decimal = %d, hex = 0x%x\n", st, st);
        if (WIFEXITED(st)) {
            int code = WEXITSTATUS(st);
            printf("Exit code: decimal = %d, hex = 0x%x\n", code, code);
        }
    }
    return 0;
}


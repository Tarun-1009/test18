/*
 * Running a Shell Command Using fork(), execvp(), and wait()
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
        char *args[] = {"ls", "-l", NULL};
        execvp(args[0], args);
        perror("execvp");
        exit(1);
    } else {
        wait(NULL);
        printf("Parent: command finished.\n");
    }
    return 0;
}


/*
 * Calls fork() after setting x = 1000.
 *
 * Observations:
 * 1. Value in child process: x is initially 1000 because child inherits
 *    a copy of the parent's memory space.
 * 2. When both change x: Each process modifies its own private copy (copy-on-write).
 *    Neither process affects the other's value of x.
 */

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int x = 1000;
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child sees initial x = %d\n", x);
        x = 2000;
        printf("Child changed x = %d\n", x);
    } else {
        printf("Parent sees initial x = %d\n", x);
        x = 3000;
        wait(NULL);
        printf("Parent after wait x = %d\n", x);
    }
    return 0;
}


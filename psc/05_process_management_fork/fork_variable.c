/*
 * Topic 5 - Q2: Variable Behavior Across fork()
 *
 * Observations:
 *   1. Before changing x, the child sees x = 1000 (an exact copy of parent's x).
 *   2. When both parent and child modify x, each changes only its own private
 *      copy (copy-on-write). Neither process affects the other's value of x.
 */

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int x = 1000;
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        printf("Child initial x = %d\n", x);
        x = 2000;
        printf("Child modified x = %d\n", x);
    } else {
        printf("Parent initial x = %d\n", x);
        x = 3000;
        wait(NULL);
        printf("Parent after child exit x = %d\n", x);
    }
    return 0;
}


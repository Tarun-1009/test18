#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

// Assignment 3 - Q2: Variable value before and after fork
int main() {
    int x = 1000;
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child sees x = %d\n", x);
        x = x + 500;
        printf("Child changed x to %d\n", x);
    } else {
        wait(NULL);
        printf("Parent sees x = %d\n", x);
        x = x - 200;
        printf("Parent changed x to %d\n", x);
    }
    // Observation: Child gets its own copy (1000). Changes in child do not affect parent.
    return 0;
}

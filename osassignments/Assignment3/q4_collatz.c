#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Assignment 3 - Q4: Collatz conjecture in child process
int main(int argc, char *argv[]) {
    int n = (argc > 1) ? atoi(argv[1]) : 8; // Default 8 if not given

    pid_t pid = fork();
    if (pid == 0) {
        printf("Collatz sequence: %d", n);
        while (n != 1) {
            n = (n % 2 == 0) ? (n / 2) : (3 * n + 1);
            printf(", %d", n);
        }
        printf("\n");
    } else {
        wait(NULL);
    }
    return 0;
}

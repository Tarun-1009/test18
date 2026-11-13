/*
 * Topic 5 - Q4: Collatz Conjecture Using fork() and wait()
 *
 * Usage: ./q4_collatz_fork 35
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <positive_integer>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Please provide a positive integer.\n");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        printf("%d", n);
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


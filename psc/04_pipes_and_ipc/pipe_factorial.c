/*
 * Topic 4 - Q1: Factorial Using Anonymous Pipe and fork()
 *
 * Parent reads a number from the user and writes it to the pipe.
 * Child reads the number, computes its factorial, and prints it.
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid > 0) {
        int n;
        close(fd[0]);
        printf("Enter a non-negative integer: ");
        scanf("%d", &n);
        write(fd[1], &n, sizeof(n));
        close(fd[1]);
        wait(NULL);
    } else {
        int n;
        close(fd[1]);
        read(fd[0], &n, sizeof(n));
        close(fd[0]);

        unsigned long long fact = 1;
        for (int i = 2; i <= n; i++) {
            fact *= (unsigned long long)i;
        }
        printf("Child: Factorial of %d = %llu\n", n, fact);
    }
    return 0;
}


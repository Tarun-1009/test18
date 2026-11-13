#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

// Assignment 4 - Q1: Factorial using pipe
int main() {
    int fd[2];
    pipe(fd);

    pid_t pid = fork();
    if (pid == 0) {
        close(fd[1]); // Close write end
        int n;
        read(fd[0], &n, sizeof(n));
        close(fd[0]);

        long long fact = 1;
        for (int i = 1; i <= n; i++) fact *= i;
        printf("[Child] Factorial of %d = %lld\n", n, fact);
    } else {
        close(fd[0]); // Close read end
        int n;
        printf("[Parent] Enter number: ");
        scanf("%d", &n);
        write(fd[1], &n, sizeof(n));
        close(fd[1]);
        wait(NULL);
    }
    return 0;
}

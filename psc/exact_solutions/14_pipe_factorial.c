/*
 * Parent takes number from user, writes into pipe.
 * Child reads from pipe and computes factorial.
 */

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int fd[2];
    pipe(fd);

    if (fork() > 0) {
        int n;
        close(fd[0]);
        printf("Enter number: ");
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
        for (int i = 2; i <= n; i++) fact *= i;
        printf("Child: Factorial of %d = %llu\n", n, fact);
    }
    return 0;
}


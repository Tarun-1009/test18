/*
 * Collatz conjecture: child generates sequence from command-line starting number.
 * n = n/2 (if even), n = 3*n + 1 (if odd) until reaching 1.
 * Parent invokes wait().
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <positive_int>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }

    if (fork() == 0) {
        printf("%d", n);
        while (n != 1) {
            if (n % 2 == 0) n = n / 2;
            else n = 3 * n + 1;
            printf(", %d", n);
        }
        printf("\n");
        exit(0);
    } else {
        wait(NULL);
    }
    return 0;
}


/*
 * Read 20 characters of F1.txt into F2.txt.
 * Uses O_APPEND so F2.txt is not deleted or overwritten.
 */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    int f1 = open("F1.txt", O_RDONLY);
    if (f1 < 0) {
        perror("F1.txt");
        return 1;
    }

    int f2 = open("F2.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (f2 < 0) {
        perror("F2.txt");
        close(f1);
        return 1;
    }

    char buf[20];
    int n = read(f1, buf, 20);
    if (n > 0) {
        write(f2, buf, n);
        printf("Appended %d characters from F1.txt to F2.txt\n", n);
    }

    close(f1);
    close(f2);
    return 0;
}


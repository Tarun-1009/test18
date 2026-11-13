/*
 * Topic 6 - Q3: Read 20 Characters from F1.txt and Append to F2.txt
 *
 * Uses O_APPEND on F2.txt so existing contents are preserved.
 */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    int f1 = open("F1.txt", O_RDONLY);
    if (f1 < 0) {
        perror("open F1.txt");
        return 1;
    }

    int f2 = open("F2.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (f2 < 0) {
        perror("open F2.txt");
        close(f1);
        return 1;
    }

    char buf[20];
    ssize_t n = read(f1, buf, 20);
    if (n > 0) {
        write(f2, buf, (size_t)n);
        printf("Appended %zd characters from F1.txt to F2.txt\n", n);
    }

    close(f1);
    close(f2);
    return 0;
}


/*
 * Topic 6 - Q6: Copy Characters 15th to 20th of F1.txt into F2.txt
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

    int f2 = open("F2.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (f2 < 0) {
        perror("open F2.txt");
        close(f1);
        return 1;
    }

    /* 15th character is at 0-based index 14; 15th through 20th = 6 characters */
    lseek(f1, 14, SEEK_SET);
    char buf[6];
    ssize_t n = read(f1, buf, 6);
    if (n > 0) {
        write(f2, buf, (size_t)n);
        printf("Wrote %zd characters (15th-20th) to F2.txt\n", n);
    }

    close(f1);
    close(f2);
    return 0;
}


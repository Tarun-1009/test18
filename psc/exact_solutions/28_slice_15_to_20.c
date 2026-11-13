/*
 * Print characters starting from 15th character till 20th character
 * of file F1.txt into file F2.txt.
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

    int f2 = open("F2.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (f2 < 0) {
        perror("F2.txt");
        close(f1);
        return 1;
    }

    /* 15th char is at offset 14; 15th to 20th = 6 characters */
    lseek(f1, 14, SEEK_SET);
    char buf[6];
    int n = read(f1, buf, 6);
    if (n > 0) {
        write(f2, buf, n);
        printf("Wrote %d characters (15th-20th) from F1.txt to F2.txt\n", n);
    }

    close(f1);
    close(f2);
    return 0;
}


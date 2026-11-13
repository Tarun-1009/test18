/*
 * Print last 5 characters of a file using open() and lseek().
 * Usage: ./a.out <filename>
 */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    off_t sz = lseek(fd, 0, SEEK_END);
    off_t off = (sz >= 5) ? (sz - 5) : 0;
    lseek(fd, off, SEEK_SET);

    char buf[6];
    int n = read(fd, buf, 5);
    if (n > 0) {
        buf[n] = '\0';
        printf("Last %d characters: %s\n", n, buf);
    }

    close(fd);
    return 0;
}


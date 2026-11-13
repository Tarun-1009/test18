/*
 * Topic 6 - Q5: Print Last 5 Characters of a File Using open() and lseek()
 *
 * Usage: ./q5_last_5_chars <filename>
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

    off_t size = lseek(fd, 0, SEEK_END);
    off_t offset = (size >= 5) ? (size - 5) : 0;
    lseek(fd, offset, SEEK_SET);

    char buf[6];
    ssize_t n = read(fd, buf, 5);
    if (n > 0) {
        buf[n] = '\0';
        printf("Last %zd characters: %s\n", n, buf);
    }

    close(fd);
    return 0;
}


/*
 * Simulate Linux 'cp' Command Using POSIX System Calls
 *
 * Usage: ./cmd_cp <source> <destination>
 */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }

    int in = open(argv[1], O_RDONLY);
    if (in < 0) {
        perror("open source");
        return 1;
    }

    int out = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (out < 0) {
        perror("open destination");
        close(in);
        return 1;
    }

    char buf[4096];
    ssize_t n;
    while ((n = read(in, buf, sizeof(buf))) > 0) {
        write(out, buf, (size_t)n);
    }

    close(in);
    close(out);
    printf("Copied %s to %s\n", argv[1], argv[2]);
    return 0;
}


/*
 * Topic 4 - Q4(a): Named Pipe Reader (my_npipe_reader.c)
 *
 * Start this reader first in one terminal, then run q4_my_npipe_writer in another.
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PIPE_PATH "/tmp/mypipe"
#define BUF_SIZE 256

int main(void) {
    unlink(PIPE_PATH);
    printf("Creating named pipe: %s\n", PIPE_PATH);
    if (mkfifo(PIPE_PATH, 0666) == -1) {
        perror("mkfifo");
        return 1;
    }

    int fd = open(PIPE_PATH, O_RDONLY);
    if (fd == -1) {
        perror("open");
        unlink(PIPE_PATH);
        return 1;
    }

    char buf[BUF_SIZE];
    while (1) {
        printf("Waiting for input...");
        fflush(stdout);
        ssize_t n = read(fd, buf, sizeof(buf) - 1);
        if (n <= 0) break;
        buf[n] = '\0';
        printf("Got it: '%s'\n", buf);
        if (strcmp(buf, "exit") == 0) {
            break;
        }
    }

    printf("Exiting\n");
    close(fd);
    unlink(PIPE_PATH);
    return 0;
}


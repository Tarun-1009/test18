/*
 * my_npipe_reader: sets up named pipe /tmp/mypipe, reads strings until 'exit'.
 */

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO "/tmp/mypipe"

int main(void) {
    unlink(FIFO);
    printf("Creating named pipe: %s\n", FIFO);
    mkfifo(FIFO, 0666);

    int fd = open(FIFO, O_RDONLY);
    char buf[256];

    while (1) {
        printf("Waiting for input...");
        fflush(stdout);
        int n = read(fd, buf, sizeof(buf) - 1);
        if (n <= 0) break;
        buf[n] = '\0';
        printf("Got it: '%s'\n", buf);
        if (strcmp(buf, "exit") == 0) break;
    }

    printf("Exiting\n");
    close(fd);
    unlink(FIFO);
    return 0;
}


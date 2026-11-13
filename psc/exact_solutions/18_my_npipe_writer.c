/*
 * my_npipe_writer: opens named pipe /tmp/mypipe, reads from user and writes to pipe.
 */

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define FIFO "/tmp/mypipe"

int main(void) {
    printf("Opening named pipe: %s\n", FIFO);
    int fd = open(FIFO, O_WRONLY);
    char buf[256];

    while (1) {
        printf("Enter Input: ");
        if (!fgets(buf, sizeof(buf), stdin)) break;
        buf[strcspn(buf, "\n")] = '\0';

        printf("Writing buffer to pipe...");
        fflush(stdout);
        write(fd, buf, strlen(buf) + 1);
        printf("done\n");

        if (strcmp(buf, "exit") == 0) break;
    }

    printf("Exiting\n");
    close(fd);
    return 0;
}


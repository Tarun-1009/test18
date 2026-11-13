#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_PATH "/tmp/mypipe"
#define BUFFER_SIZE 256

/*
 * Assignment 4 - Question 4:
 * my_npipe_writer.c
 * Opens named pipe /tmp/mypipe, reads strings from user and writes them.
 * Exits after writing 'exit'.
 */

int main() {
    printf("Opening named pipe: %s\n", FIFO_PATH);

    char buffer[BUFFER_SIZE];

    while (1) {
        printf("Enter Input: ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            strcpy(buffer, "exit");
        }

        // Remove newline
        buffer[strcspn(buffer, "\r\n")] = '\0';

        // Open named pipe for writing (blocks until reader opens it)
        int fd = open(FIFO_PATH, O_WRONLY);
        if (fd < 0) {
            perror("Error opening pipe (Make sure reader is running first)");
            sleep(1);
            continue;
        }

        write(fd, buffer, strlen(buffer) + 1);
        printf("Writing buffer to pipe...done\n");
        close(fd);

        if (strcmp(buffer, "exit") == 0) {
            break;
        }
    }

    printf("Exiting\n");
    return 0;
}


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
 * my_npipe_reader.c
 * Creates named pipe /tmp/mypipe, reads strings until 'exit' is received.
 */

int main() {
    // Unlink old pipe if exists, then create named pipe
    unlink(FIFO_PATH);
    if (mkfifo(FIFO_PATH, 0666) == -1) {
        perror("mkfifo failed");
        return 1;
    }

    printf("Creating named pipe: %s\n", FIFO_PATH);

    char buffer[BUFFER_SIZE];

    while (1) {
        printf("Waiting for input...");
        fflush(stdout);

        // Open pipe for reading (blocks until a writer opens it)
        int fd = open(FIFO_PATH, O_RDONLY);
        if (fd < 0) {
            perror("open failed");
            break;
        }

        ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
        close(fd);

        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            // Strip any trailing newline
            buffer[strcspn(buffer, "\r\n")] = '\0';

            printf("Got it: '%s'\n", buffer);

            if (strcmp(buffer, "exit") == 0) {
                break;
            }
        }
    }

    printf("Exiting\n");
    unlink(FIFO_PATH); // Clean up FIFO file
    return 0;
}


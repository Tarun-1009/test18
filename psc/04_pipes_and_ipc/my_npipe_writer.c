/*
 * Topic 4 - Q4(b): Named Pipe Writer (my_npipe_writer.c)
 *
 * Run after starting q4_my_npipe_reader in another terminal.
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
    printf("Opening named pipe: %s\n", PIPE_PATH);
    int fd = open(PIPE_PATH, O_WRONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char buf[BUF_SIZE];
    while (1) {
        printf("Enter Input: ");
        if (!fgets(buf, sizeof(buf), stdin)) break;
        buf[strcspn(buf, "\n")] = '\0';

        printf("Writing buffer to pipe...");
        fflush(stdout);
        write(fd, buf, strlen(buf) + 1);
        printf("done\n");

        if (strcmp(buf, "exit") == 0) {
            break;
        }
    }

    printf("Exiting\n");
    close(fd);
    return 0;
}


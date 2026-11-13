/*
 * Opens a file with open(), then calls fork().
 *
 * Observations:
 * 1. Can both access fd? Yes, child inherits a duplicate of the parent's file descriptor table.
 * 2. What happens when writing concurrently? Both descriptors point to the same open file
 *    description and share the file offset. The writes are interleaved without overwriting.
 */

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int fd = open("test_fork_file.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    pid_t pid = fork();

    const char *msg = (pid == 0) ? "Child write\n" : "Parent write\n";
    for (int i = 0; i < 5; i++) {
        write(fd, msg, strlen(msg));
        usleep(1000);
    }

    if (pid > 0) {
        wait(NULL);
        printf("Parent and child wrote to test_fork_file.txt successfully.\n");
    }
    close(fd);
    return 0;
}


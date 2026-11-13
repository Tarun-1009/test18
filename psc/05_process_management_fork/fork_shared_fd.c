/*
 * Topic 5 - Q3: Shared File Descriptor Across fork()
 *
 * Observations:
 *   1. Yes, both parent and child can access the file descriptor returned by open()
 *      before fork(), because the child inherits a copy of the parent's fd table.
 *   2. Both descriptors point to the same open file description (sharing the file
 *      offset). When writing concurrently, writes do not overwrite each other's
 *      offset, so both outputs appear in the file, interleaved in scheduling order.
 */

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int fd = open("fork_shared_output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        close(fd);
        return 1;
    }

    const char *msg = (pid == 0) ? "Child line\n" : "Parent line\n";
    for (int i = 0; i < 5; i++) {
        write(fd, msg, strlen(msg));
        usleep(1000);
    }

    if (pid > 0) {
        wait(NULL);
        printf("Finished writing to fork_shared_output.txt\n");
    }
    close(fd);
    return 0;
}


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

// Assignment 3 - Q3: File descriptor sharing across fork
int main() {
    int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    pid_t pid = fork();

    if (pid == 0) {
        write(fd, "Child writing...\n", 17);
    } else {
        wait(NULL);
        write(fd, "Parent writing...\n", 18);
        close(fd);
    }
    // Observation: Both access fd. Because they share kernel file offset,
    // they write sequentially without overwriting each other.
    return 0;
}

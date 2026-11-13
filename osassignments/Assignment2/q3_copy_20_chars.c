#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/*
 * Assignment 2 - Question 3:
 * Write a C program to read some content (20 characters) of file F1.txt
 * into file F2.txt. The contents of file F2 should not get deleted or overwritten.
 */

int main() {
    // Open F1.txt in read-only mode
    int fd_in = open("F1.txt", O_RDONLY);
    if (fd_in < 0) {
        perror("Error opening F1.txt");
        return 1;
    }

    // Open F2.txt with O_WRONLY | O_CREAT | O_APPEND so existing content is preserved
    int fd_out = open("F2.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd_out < 0) {
        perror("Error opening F2.txt");
        close(fd_in);
        return 1;
    }

    char buffer[21];
    ssize_t bytes_read = read(fd_in, buffer, 20);
    if (bytes_read < 0) {
        perror("Error reading from F1.txt");
        close(fd_in);
        close(fd_out);
        return 1;
    }

    ssize_t bytes_written = write(fd_out, buffer, bytes_read);
    if (bytes_written < 0) {
        perror("Error writing to F2.txt");
    } else {
        printf("Successfully appended %zd characters from F1.txt to F2.txt.\n", bytes_written);
    }

    close(fd_in);
    close(fd_out);
    return 0;
}


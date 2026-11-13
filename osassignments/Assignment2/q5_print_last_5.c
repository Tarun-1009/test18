#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/*
 * Assignment 2 - Question 5:
 * Write a C program using open() and lseek() system calls to print
 * the last 5 characters of a file on the screen.
 */

int main(int argc, char *argv[]) {
    const char *filename = (argc > 1) ? argv[1] : "F1.txt";

    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }

    // Check file size
    off_t filesize = lseek(fd, 0, SEEK_END);
    if (filesize < 0) {
        perror("Error using lseek");
        close(fd);
        return 1;
    }

    if (filesize < 5) {
        printf("File '%s' has fewer than 5 characters (size: %ld bytes).\n", filename, (long)filesize);
        lseek(fd, 0, SEEK_SET);
    } else {
        // Move offset to 5 bytes before the end of the file
        lseek(fd, -5, SEEK_END);
    }

    char buffer[6];
    ssize_t bytes_read = read(fd, buffer, 5);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        printf("Last %zd characters of '%s': \"%s\"\n", bytes_read, filename, buffer);
    } else {
        perror("Error reading file");
    }

    close(fd);
    return 0;
}


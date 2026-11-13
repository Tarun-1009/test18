#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/*
 * Assignment 2 - Question 6:
 * Write a C program to print characters starting from 15th character
 * till the 20th character of file F1.txt into the file F2.txt.
 * (15th character is at offset 14; 15th to 20th inclusive is 6 characters: 15,16,17,18,19,20).
 */

int main() {
    int fd_in = open("F1.txt", O_RDONLY);
    if (fd_in < 0) {
        perror("Error opening F1.txt");
        return 1;
    }

    int fd_out = open("F2.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd_out < 0) {
        perror("Error opening F2.txt");
        close(fd_in);
        return 1;
    }

    // Move file pointer to the 15th character (0-based index 14)
    off_t offset = lseek(fd_in, 14, SEEK_SET);
    if (offset == -1) {
        perror("Error seeking to 15th character");
        close(fd_in);
        close(fd_out);
        return 1;
    }

    // Number of characters from 15th through 20th = 6 characters
    char buffer[7];
    ssize_t bytes_read = read(fd_in, buffer, 6);
    if (bytes_read < 0) {
        perror("Error reading from F1.txt");
    } else {
        buffer[bytes_read] = '\0';
        write(fd_out, buffer, bytes_read);
        printf("Extracted %zd characters (\"%s\") from F1.txt into F2.txt.\n", bytes_read, buffer);
    }

    close(fd_in);
    close(fd_out);
    return 0;
}


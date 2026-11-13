#include <stdio.h>
#include <unistd.h>

/*
 * Assignment 2 - Question 2:
 * Write a C program to read a maximum of 15 characters from the user
 * and print them on the screen using system calls.
 */

int main() {
    char buffer[16]; // 15 characters + null terminator
    ssize_t bytes_read;

    write(STDOUT_FILENO, "Enter some text (max 15 characters): ", 37);

    // Read up to 15 characters from standard input (stdin fd = 0)
    bytes_read = read(STDIN_FILENO, buffer, 15);

    if (bytes_read < 0) {
        perror("read failed");
        return 1;
    }

    buffer[bytes_read] = '\0';

    write(STDOUT_FILENO, "\nYou entered: ", 14);
    write(STDOUT_FILENO, buffer, bytes_read);
    write(STDOUT_FILENO, "\n", 1);

    return 0;
}


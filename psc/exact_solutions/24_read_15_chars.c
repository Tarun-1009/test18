/*
 * Read a maximum of 15 characters from the user and print on screen.
 */

#include <stdio.h>
#include <unistd.h>

int main(void) {
    char buf[16];
    printf("Enter text: ");
    fflush(stdout);

    int n = read(STDIN_FILENO, buf, 15);
    if (n > 0) {
        buf[n] = '\0';
        printf("Read 15 chars max: %s\n", buf);
    }
    return 0;
}


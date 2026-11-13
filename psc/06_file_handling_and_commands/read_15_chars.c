/*
 * Topic 6 - Q2: Read Maximum of 15 Characters from User and Print
 */

#include <stdio.h>
#include <unistd.h>

int main(void) {
    char buf[16];
    printf("Enter text (max 15 chars will be read): ");
    fflush(stdout);

    ssize_t n = read(STDIN_FILENO, buf, 15);
    if (n > 0) {
        buf[n] = '\0';
        printf("Read (%zd chars): %s\n", n, buf);
    }
    return 0;
}


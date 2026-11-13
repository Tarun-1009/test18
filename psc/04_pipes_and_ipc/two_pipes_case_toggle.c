/*
 * Topic 4 - Q2: Two-Way Communication Using Two Pipes (Toggle Case)
 *
 * Parent sends a string to Child via pipe1.
 * Child toggles the case of each letter and sends it back via pipe2.
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LEN 256

int main(void) {
    int p2c[2], c2p[2];
    if (pipe(p2c) == -1 || pipe(c2p) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid > 0) {
        char msg[MAX_LEN];
        close(p2c[0]);
        close(c2p[1]);

        printf("Enter a message: ");
        fgets(msg, sizeof(msg), stdin);

        write(p2c[1], msg, strlen(msg) + 1);
        close(p2c[1]);

        read(c2p[0], msg, sizeof(msg));
        close(c2p[0]);

        printf("Parent received toggled message: %s", msg);
        wait(NULL);
    } else {
        char buf[MAX_LEN];
        close(p2c[1]);
        close(c2p[0]);

        read(p2c[0], buf, sizeof(buf));
        close(p2c[0]);

        for (int i = 0; buf[i] != '\0'; i++) {
            if (islower((unsigned char)buf[i])) {
                buf[i] = (char)toupper((unsigned char)buf[i]);
            } else if (isupper((unsigned char)buf[i])) {
                buf[i] = (char)tolower((unsigned char)buf[i]);
            }
        }

        write(c2p[1], buf, strlen(buf) + 1);
        close(c2p[1]);
    }
    return 0;
}


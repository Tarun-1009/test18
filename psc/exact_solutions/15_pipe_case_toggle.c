/*
 * Parent sends message via pipe. Child toggles case and returns via pipe.
 * Parent displays toggled message.
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int p1[2], p2[2];
    pipe(p1);
    pipe(p2);

    if (fork() > 0) {
        char s[256];
        close(p1[0]);
        close(p2[1]);

        printf("Enter message: ");
        fgets(s, sizeof(s), stdin);
        write(p1[1], s, strlen(s) + 1);
        close(p1[1]);

        read(p2[0], s, sizeof(s));
        close(p2[0]);
        printf("Parent received: %s", s);
        wait(NULL);
    } else {
        char s[256];
        close(p1[1]);
        close(p2[0]);

        read(p1[0], s, sizeof(s));
        close(p1[0]);

        for (int i = 0; s[i]; i++) {
            if (islower(s[i])) s[i] = toupper(s[i]);
            else if (isupper(s[i])) s[i] = tolower(s[i]);
        }

        write(p2[1], s, strlen(s) + 1);
        close(p2[1]);
    }
    return 0;
}


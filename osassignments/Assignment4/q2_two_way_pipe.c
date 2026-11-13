#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <sys/wait.h>

// Assignment 4 - Q2: Two-way pipe case toggling
int main() {
    int p1[2], p2[2];
    pipe(p1); // Parent -> Child
    pipe(p2); // Child -> Parent

    if (fork() == 0) {
        close(p1[1]); close(p2[0]);
        char str[100];
        read(p1[0], str, sizeof(str));
        for (int i = 0; str[i]; i++) {
            if (islower(str[i])) str[i] = toupper(str[i]);
            else if (isupper(str[i])) str[i] = tolower(str[i]);
        }
        write(p2[1], str, strlen(str) + 1);
        close(p1[0]); close(p2[1]);
    } else {
        close(p1[0]); close(p2[1]);
        char msg[100];
        printf("Enter message: ");
        fgets(msg, sizeof(msg), stdin);
        msg[strcspn(msg, "\n")] = 0;

        write(p1[1], msg, strlen(msg) + 1);
        close(p1[1]);

        read(p2[0], msg, sizeof(msg));
        close(p2[0]);
        wait(NULL);
        printf("Result from child: %s\n", msg);
    }
    return 0;
}

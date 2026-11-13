/*
 * Parent writes sentence to named pipe.
 * Child reads sentence, counts vowels, and prints both.
 */

#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define FIFO "/tmp/vow_fifo"

int main(void) {
    unlink(FIFO);
    mkfifo(FIFO, 0666);

    if (fork() > 0) {
        char s[256];
        printf("<Parent Process>\nPlease enter a sentence: ");
        fgets(s, sizeof(s), stdin);
        s[strcspn(s, "\n")] = '\0';

        int fd = open(FIFO, O_WRONLY);
        write(fd, s, strlen(s) + 1);
        printf("Parent process: Write the sentence into the pipe.\n");
        close(fd);

        wait(NULL);
        unlink(FIFO);
    } else {
        char s[256];
        int fd = open(FIFO, O_RDONLY);
        read(fd, s, sizeof(s));
        close(fd);

        int v = 0;
        for (int i = 0; s[i]; i++) {
            char c = tolower(s[i]);
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') v++;
        }
        printf("<Child Process>\nRead %s, number of vowels =%d\n", s, v);
    }
    return 0;
}


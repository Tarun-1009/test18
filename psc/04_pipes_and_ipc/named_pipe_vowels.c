/*
 * Topic 4 - Q3: Vowel Counter Using Named Pipe (FIFO) and fork()
 *
 * Parent reads a sentence and writes it to a named pipe.
 * Child reads the sentence from the named pipe and counts vowels.
 */

#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define FIFO_PATH "/tmp/vowel_fifo"
#define MAX_LEN 256

int main(void) {
    unlink(FIFO_PATH);
    if (mkfifo(FIFO_PATH, 0666) == -1) {
        perror("mkfifo");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid > 0) {
        char sentence[MAX_LEN];
        printf("<Parent Process>\nPlease enter a sentence: ");
        fgets(sentence, sizeof(sentence), stdin);
        sentence[strcspn(sentence, "\n")] = '\0';

        int fd = open(FIFO_PATH, O_WRONLY);
        write(fd, sentence, strlen(sentence) + 1);
        printf("Parent process: Write the sentence into the pipe.\n");
        close(fd);

        wait(NULL);
        unlink(FIFO_PATH);
    } else {
        char buf[MAX_LEN];
        int fd = open(FIFO_PATH, O_RDONLY);
        read(fd, buf, sizeof(buf));
        close(fd);

        int vowels = 0;
        for (int i = 0; buf[i] != '\0'; i++) {
            char ch = (char)tolower((unsigned char)buf[i]);
            if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
                vowels++;
            }
        }
        printf("<Child Process>\nRead %s, number of vowels = %d\n", buf, vowels);
    }
    return 0;
}


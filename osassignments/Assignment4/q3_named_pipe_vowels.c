#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>

// Assignment 4 - Q3: Named pipe (FIFO) vowel counting
int main() {
    char *fifo = "/tmp/my_fifo";
    unlink(fifo);
    mkfifo(fifo, 0666);

    if (fork() == 0) {
        int fd = open(fifo, O_RDONLY);
        char s[100];
        read(fd, s, sizeof(s));
        close(fd);

        int vowels = 0;
        for (int i = 0; s[i]; i++) {
            char c = tolower(s[i]);
            if (c=='a' || c=='e' || c=='i' || c=='o' || c=='u') vowels++;
        }
        printf("<Child Process>\nRead %s, number of vowels =%d\n", s, vowels);
    } else {
        char s[100];
        printf("<Parent Process>\nPlease enter a sentence: ");
        fgets(s, sizeof(s), stdin);
        s[strcspn(s, "\n")] = 0;

        int fd = open(fifo, O_WRONLY);
        write(fd, s, strlen(s) + 1);
        printf("Parent process: Write the sentence into the pipe.\n");
        close(fd);

        wait(NULL);
        unlink(fifo);
    }
    return 0;
}

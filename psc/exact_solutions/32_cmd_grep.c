/*
 * Simulate Linux 'grep' command.
 * Usage: ./a.out <pattern> <filename>
 */

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <pattern> <filename>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[2], "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    char line[512];
    int ln = 1;
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, argv[1])) {
            printf("%d: %s", ln, line);
        }
        ln++;
    }

    fclose(fp);
    return 0;
}


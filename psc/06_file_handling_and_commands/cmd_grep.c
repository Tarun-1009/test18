/*
 * Topic 6 - Q7(iv): Simulate Linux 'grep' Command
 *
 * Usage: ./q7_grep <pattern> <filename>
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

    char line[1024];
    int line_no = 1;
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strstr(line, argv[1]) != NULL) {
            printf("%d: %s", line_no, line);
        }
        line_no++;
    }

    fclose(fp);
    return 0;
}


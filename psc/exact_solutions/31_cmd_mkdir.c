/*
 * Simulate Linux 'mkdir' command.
 * Usage: ./a.out <directory_name>
 */

#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <dir_name>\n", argv[0]);
        return 1;
    }

    if (mkdir(argv[1], 0755) != 0) {
        perror("mkdir");
        return 1;
    }
    printf("Directory '%s' created.\n", argv[1]);
    return 0;
}


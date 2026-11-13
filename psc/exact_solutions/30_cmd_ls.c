/*
 * Simulate Linux 'ls' command.
 * Usage: ./a.out [directory]
 */

#include <dirent.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    const char *path = (argc > 1) ? argv[1] : ".";
    DIR *d = opendir(path);
    if (!d) {
        perror("opendir");
        return 1;
    }

    struct dirent *de;
    while ((de = readdir(d)) != NULL) {
        if (de->d_name[0] != '.') {
            printf("%s\n", de->d_name);
        }
    }
    closedir(d);
    return 0;
}


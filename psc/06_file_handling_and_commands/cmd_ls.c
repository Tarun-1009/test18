/*
 * Topic 6 - Q7(ii): Simulate Linux 'ls' Command
 *
 * Usage: ./q7_ls [directory]
 */

#include <dirent.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    const char *path = (argc > 1) ? argv[1] : ".";
    DIR *dir = opendir(path);
    if (!dir) {
        perror("ls");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {
            printf("%s\n", entry->d_name);
        }
    }
    closedir(dir);
    return 0;
}


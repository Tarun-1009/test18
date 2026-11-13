/*
 * Display File Metadata Using stat()
 *
 * Usage: ./file_stat_info <path>
 */

#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <path>\n", argv[0]);
        return 1;
    }

    struct stat st;
    if (stat(argv[1], &st) != 0) {
        perror("stat");
        return 1;
    }

    printf("File: %s\n", argv[1]);
    printf("Type: %s\n", S_ISDIR(st.st_mode) ? "Directory" : "Regular File");
    printf("Size: %lld bytes\n", (long long)st.st_size);
    printf("Links: %u\n", (unsigned int)st.st_nlink);
    printf("Permissions (octal): %o\n", st.st_mode & 0777);
    printf("Last modified: %s", ctime(&st.st_mtime));
    return 0;
}


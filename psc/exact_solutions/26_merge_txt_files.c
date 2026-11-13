/*
 * Merge all .txt files in the current directory into one new .txt file
 * and return the file descriptor for the new file.
 */

#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int merge_txt(const char *out_name) {
    int out_fd = open(out_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
    DIR *d = opendir(".");
    struct dirent *de;
    char buf[512];

    while ((de = readdir(d)) != NULL) {
        int len = strlen(de->d_name);
        if (len > 4 && strcmp(de->d_name + len - 4, ".txt") == 0 &&
            strcmp(de->d_name, out_name) != 0) {
            int in_fd = open(de->d_name, O_RDONLY);
            if (in_fd >= 0) {
                int n;
                while ((n = read(in_fd, buf, sizeof(buf))) > 0) {
                    write(out_fd, buf, n);
                }
                write(out_fd, "\n", 1);
                close(in_fd);
            }
        }
    }
    closedir(d);
    return out_fd;
}

int main(void) {
    int fd = merge_txt("merged_all.txt");
    printf("Merged all .txt files into merged_all.txt, returned fd = %d\n", fd);
    close(fd);
    return 0;
}


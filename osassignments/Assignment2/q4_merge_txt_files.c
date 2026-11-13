#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

// Assignment 2 - Q4: Merge all .txt files into one
int main() {
    DIR *d = opendir(".");
    struct dirent *dir;
    char buf[256];
    int out_fd = open("merged.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    while ((dir = readdir(d)) != NULL) {
        int len = strlen(dir->d_name);
        if (len > 4 && strcmp(dir->d_name + len - 4, ".txt") == 0 && strcmp(dir->d_name, "merged.txt") != 0) {
            int in_fd = open(dir->d_name, O_RDONLY);
            int n;
            while ((n = read(in_fd, buf, sizeof(buf))) > 0) {
                write(out_fd, buf, n);
            }
            close(in_fd);
        }
    }
    closedir(d);
    printf("Merged all .txt files. File descriptor: %d\n", out_fd);
    close(out_fd);
    return 0;
}

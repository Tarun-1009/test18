/*
 * Topic 6 - Q4: Merge All .txt Files in Current Directory into One .txt File
 *
 * Function merge_txt_files() creates "merged_output.txt", copies all other
 * .txt files into it, and returns its open file descriptor.
 */

#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int merge_txt_files(const char *out_name) {
    int out_fd = open(out_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (out_fd < 0) {
        perror("open output");
        return -1;
    }

    DIR *dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return out_fd;
    }

    struct dirent *entry;
    char buf[1024];
    while ((entry = readdir(dir)) != NULL) {
        size_t len = strlen(entry->d_name);
        if (len > 4 && strcmp(entry->d_name + len - 4, ".txt") == 0 &&
            strcmp(entry->d_name, out_name) != 0) {
            int in_fd = open(entry->d_name, O_RDONLY);
            if (in_fd >= 0) {
                ssize_t n;
                while ((n = read(in_fd, buf, sizeof(buf))) > 0) {
                    write(out_fd, buf, (size_t)n);
                }
                write(out_fd, "\n", 1);
                close(in_fd);
            }
        }
    }
    closedir(dir);
    return out_fd;
}

int main(void) {
    int fd = merge_txt_files("merged_output.txt");
    if (fd >= 0) {
        printf("Merged .txt files into merged_output.txt (fd = %d)\n", fd);
        close(fd);
    }
    return 0;
}


/*
 * Topic 6 - Q1: File Operations Using POSIX System Calls
 *   (i)   Create a file
 *   (ii)  Read contents of a file
 *   (iii) Write to a file
 *   (iv)  Link and unlink a file
 *   (v)   Copy file
 *   (vi)  Read contents of a file in reverse order
 */

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void read_file(const char *path) {
    int fd = open(path, O_RDONLY);
    if (fd < 0) { perror("open"); return; }
    char buf[128];
    ssize_t n;
    while ((n = read(fd, buf, sizeof(buf) - 1)) > 0) {
        buf[n] = '\0';
        printf("%s", buf);
    }
    close(fd);
}

void copy_file(const char *src, const char *dst) {
    int in = open(src, O_RDONLY);
    int out = open(dst, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (in < 0 || out < 0) { perror("copy"); return; }
    char buf[256];
    ssize_t n;
    while ((n = read(in, buf, sizeof(buf))) > 0) {
        write(out, buf, (size_t)n);
    }
    close(in);
    close(out);
}

void read_reverse(const char *path) {
    int fd = open(path, O_RDONLY);
    if (fd < 0) { perror("open"); return; }
    off_t size = lseek(fd, 0, SEEK_END);
    char ch;
    for (off_t pos = size - 1; pos >= 0; pos--) {
        lseek(fd, pos, SEEK_SET);
        read(fd, &ch, 1);
        putchar(ch);
    }
    putchar('\n');
    close(fd);
}

int main(void) {
    const char *file = "demo.txt";
    const char *hardlink = "demo_link.txt";
    const char *copy = "demo_copy.txt";

    /* (i) Create & (iii) Write */
    int fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    const char *text = "Hello OS Lab!";
    write(fd, text, strlen(text));
    close(fd);
    printf("(i, iii) Created and wrote to %s\n", file);

    /* (ii) Read */
    printf("(ii) Contents: ");
    read_file(file);
    printf("\n");

    /* (iv) Link and Unlink */
    if (link(file, hardlink) == 0) {
        printf("(iv) Created hard link %s\n", hardlink);
        unlink(hardlink);
        printf("(iv) Unlinked %s\n", hardlink);
    }

    /* (v) Copy */
    copy_file(file, copy);
    printf("(v) Copied %s to %s\n", file, copy);

    /* (vi) Read in reverse */
    printf("(vi) Reverse contents: ");
    read_reverse(file);

    return 0;
}


/*
 * Implement file operations using system calls:
 * (i) Create a file
 * (ii) Read contents
 * (iii) Write to file
 * (iv) Link and unlink
 * (v) Copy file
 * (vi) Read in reverse order
 */

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void show_file(const char *fn) {
    int fd = open(fn, O_RDONLY);
    char buf[128];
    int n;
    while ((n = read(fd, buf, sizeof(buf) - 1)) > 0) {
        buf[n] = '\0';
        printf("%s", buf);
    }
    close(fd);
}

int main(void) {
    const char *f1 = "file1.txt";
    const char *f2 = "file2.txt";
    const char *lnk = "file_link.txt";

    /* (i) Create & (iii) Write */
    int fd = open(f1, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    const char *msg = "Operating Systems Lab!";
    write(fd, msg, strlen(msg));
    close(fd);
    printf("(i, iii) Created and wrote to %s\n", f1);

    /* (ii) Read */
    printf("(ii) Reading %s: ", f1);
    show_file(f1);
    printf("\n");

    /* (iv) Link and unlink */
    link(f1, lnk);
    printf("(iv) Created link %s\n", lnk);
    unlink(lnk);
    printf("(iv) Unlinked %s\n", lnk);

    /* (v) Copy */
    int in = open(f1, O_RDONLY);
    int out = open(f2, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    char buf[128];
    int n;
    while ((n = read(in, buf, sizeof(buf))) > 0) write(out, buf, n);
    close(in);
    close(out);
    printf("(v) Copied %s to %s\n", f1, f2);

    /* (vi) Read reverse */
    printf("(vi) Reverse of %s: ", f1);
    fd = open(f1, O_RDONLY);
    off_t sz = lseek(fd, 0, SEEK_END);
    char c;
    for (off_t i = sz - 1; i >= 0; i--) {
        lseek(fd, i, SEEK_SET);
        read(fd, &c, 1);
        putchar(c);
    }
    printf("\n");
    close(fd);

    return 0;
}


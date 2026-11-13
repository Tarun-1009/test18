#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// Assignment 2 - Q1: Simple File Operations using System Calls
int main() {
    char buf[100];
    int fd;

    // (i) Create and (iii) Write
    fd = creat("demo.txt", 0644);
    write(fd, "Hello Operating Systems Lab!\n", 29);
    close(fd);

    // (ii) Read
    fd = open("demo.txt", O_RDONLY);
    int n = read(fd, buf, sizeof(buf) - 1);
    buf[n] = '\0';
    printf("Read from file: %s", buf);
    close(fd);

    // (iv) Link and Unlink
    link("demo.txt", "demo_link.txt");
    printf("Created hard link demo_link.txt\n");
    unlink("demo_link.txt");
    printf("Unlinked demo_link.txt\n");

    // (v) Copy file
    int in = open("demo.txt", O_RDONLY);
    int out = creat("demo_copy.txt", 0644);
    while ((n = read(in, buf, sizeof(buf))) > 0) {
        write(out, buf, n);
    }
    close(in);
    close(out);
    printf("Copied demo.txt to demo_copy.txt\n");

    // (vi) Read in reverse
    fd = open("demo.txt", O_RDONLY);
    int size = lseek(fd, 0, SEEK_END);
    printf("Reverse content: ");
    char ch;
    for (int i = size - 1; i >= 0; i--) {
        lseek(fd, i, SEEK_SET);
        read(fd, &ch, 1);
        putchar(ch);
    }
    printf("\n");
    close(fd);

    return 0;
}

/*
 * Topic 6 - Q7(i): Simulate Linux 'cd' Command
 *
 * Usage: ./q7_cd <directory>
 */

#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    if (chdir(argv[1]) != 0) {
        perror("cd");
        return 1;
    }

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Changed directory to: %s\n", cwd);
    }
    return 0;
}


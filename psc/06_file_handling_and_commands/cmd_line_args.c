/*
 * Topic 6 - Q8 (Doc Q4): Command Line Arguments Demo
 *
 * Usage: ./q8_cmd_line_args arg1 arg2 ...
 */

#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("Program name: %s\n", argv[0]);
    printf("Total arguments passed: %d\n", argc - 1);
    for (int i = 1; i < argc; i++) {
        printf("  argv[%d] = %s\n", i, argv[i]);
    }
    return 0;
}


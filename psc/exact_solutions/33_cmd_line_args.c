/*
 * Demonstration of command line arguments (argc, argv).
 * Usage: ./a.out arg1 arg2 ...
 */

#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("Program Name: %s\n", argv[0]);
    printf("Number of arguments passed: %d\n", argc - 1);
    for (int i = 1; i < argc; i++) {
        printf("  Argument %d = %s\n", i, argv[i]);
    }
    return 0;
}


#include "stdio.h"
#include "stdlib.h"


void print_help() {
    printf("Prints numbers in range from M to N with step S\n");
    printf("  * If no arguments passed - prints help\n");
    printf("  * If 1 argument passed - takes it as N, M = 0; S = 1\n");
    printf("  * If 2 arguments passed - takes them as M and N; S = 1\n");
    printf("  * If 3 arguments passed - takes them as M, N and S\n");
}


int main(int argc, char** argv) {
    int n, m = 0, s = 1;

    if (argc <= 1) {
        print_help();
        return 0;
    }
    if (argc > 1) {
        n = atoi(argv[1]);
    }
    if (argc > 2) {
        m = atoi(argv[2]);
        int t = m;
        m = n;
        n = t;
    }
    if (argc > 3) {
        s = atoi(argv[3]);
    }

    for (int val = m, i = 0; val < n; i++, val += s) {
        // printf("%d ", val);
        if (28 <= i && i <= 35) {
            printf("%d %d %d %d\n", m, n, s, val);
        }
    }
    // printf("\n");

    return 0;
}

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int guess(int l, int r) {
    if (l == r) {
        printf("Your number is %d\n", l);
        return 1;
    }

    int m = (l + r) / 2;

    printf("Is your number greater than %d? (yes/no)\n", m);
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, stdin) > 0) {
        if (strcmp(line, "yes\n") == 0) {
            if (m == r) {
                printf("Your number is %d\n", m);
                return 1;
            }
            return guess(m + 1, r) + 1;
        } else if (strcmp(line, "no\n") == 0) {
            if (m == l) {
                printf("Your number is %d\n", m);
                return 1;
            }
            return guess(l, m) + 1;
        } else {
            printf("Invalid input, expected yes/no\n");
        }
    }

    printf("Error reading input\n");
    exit(1);
}

int main() {

    int number_of_guesses = guess(1, 100);

    printf("guessed in %d guesses\n", number_of_guesses);

    return 0;
}

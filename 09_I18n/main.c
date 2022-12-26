#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)


int guess(int l, int r) {
    if (l == r) {
        printf("Your number is %d\n", l);
        return 1;
    }

    int m = (l + r) / 2;

    printf("%s %d? (%s/%s)\n", _("Is your number greater than"), m, _("yes"), _("no"));
    char *line = NULL;
    size_t len = 0;
    int read;
    while ((read = getline(&line, &len, stdin)) > 0) {
        line[read - 1] = '\0';
        if (strcmp(line, _("yes")) == 0) {
            if (m == r) {
                printf("%s %d\n", _("Your number is"), m);
                return 1;
            }
            return guess(m + 1, r) + 1;
        } else if (strcmp(line, _("no")) == 0) {
            if (m == l) {
                printf("%s %d\n", _("Your number is"), m);
                return 1;
            }
            return guess(l, m) + 1;
        } else {
            printf("%s %s/%s\n", _("Invalid input, expected"), _("yes"), _("no"));
        }
    }

    printf("%s\n", _("Error reading input"));
    exit(1);
}

int main() {
    setlocale(LC_ALL, "");
    bindtextdomain("main", "..");
    textdomain ("main");

    int number_of_guesses = guess(1, 100);

    printf("guessed in %d guesses\n", number_of_guesses);

    return 0;
}

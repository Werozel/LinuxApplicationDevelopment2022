#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

const char *roman[101] = { "N", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII", "XIII", "XIV",
                           "XV", "XVI", "XVII", "XVIII", "XIX", "XX", "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI",
                           "XXVII", "XXVIII", "XXIX", "XXX", "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI",
                           "XXXVII", "XXXVIII", "XXXIX", "XL", "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII",
                           "XLVIII", "XLIX", "L", "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX",
                           "LX", "LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX",
                           "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII", "LXXIX", "LXXX",
                           "LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX",
                           "XC", "XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII", "XCIX", "C"
};

const char* toRoman(int number)
{
    if (number < 1 || number > 100)
    {
        return _("Invalid number");
    }
    return roman[number];
}

int guess(int l, int r, int isRoman) {
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
            return guess(m + 1, r, isRoman) + 1;
        } else if (strcmp(line, _("no")) == 0) {
            if (m == l) {
                printf("%s %d\n", _("Your number is"), m);
                return 1;
            }
            return guess(l, m, isRoman) + 1;
        } else {
            printf("%s %s/%s\n", _("Invalid input, expected"), _("yes"), _("no"));
        }
    }

    printf("%s\n", _("Error reading input"));
    exit(1);
}

int main(int argc, const char *argv[]) {
    int isRoman = 0;
    if (argc > 1) {
        if (strcmp(argv[1], "-r") == 0) {
            isRoman = 1;
        } else if (strcmp(argv[1], "--help") == 0) {
            printf("%s\n%s\n\t%s\n\t%s\n%s", _("A simple number guessing game"), _("Usage: main [-r, --help]"),
                   _("-r - use roman numerals"), _("--help - show this help"), _("ru and en locales are available"));
            return 0;
        }
    }

    setlocale(LC_ALL, "");
    bindtextdomain("main", getenv("PWD"));
    textdomain ("main");

    int number_of_guesses = guess(1, 100, isRoman);

    printf("%s %d\n", _("Number of guesses"),  number_of_guesses);

    return 0;
}

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

int roman_to_num(const char *roman_num) {
    for (int i = 0; i < 101; i++) {
        if (strcmp(roman_num, roman[i]) == 0) {
            return i;
        }
    }
    return -1;
}

const char* num_to_roman(int number) {
    if (number < 1 || number > 100) {
        return _("Invalid number");
    }
    return roman[number];
}

const char* num_to_str(int number, int isRoman) {
    if (isRoman) {
        return num_to_roman(number);
    } else {
        char *num_str = malloc(4 * sizeof(char));
        sprintf(num_str, "%d", number);
        return num_str;
    }
}

int guess(int l, int r, int isRoman) {
    if (l == r) {
        const char *l_str = num_to_str(l, isRoman);
        printf("%s %s\n", _("Your number is"), l_str);
        return 1;
    }

    int m = (l + r) / 2;

    const char *m_str = num_to_str(m, isRoman);
    printf("%s %s? (%s/%s)\n", _("Is your number greater than"), m_str, _("yes"), _("no"));
    char *line = NULL;
    size_t len = 0;
    int read;
    while ((read = getline(&line, &len, stdin)) > 0) {
        line[read - 1] = '\0';
        if (strcmp(line, _("yes")) == 0) {
            if (m == r) {
                printf("%s %s\n", _("Your number is"), m_str);
                return 1;
            }
            return guess(m + 1, r, isRoman) + 1;
        } else if (strcmp(line, _("no")) == 0) {
            if (m == l) {
                printf("%s %s\n", _("Your number is"), m_str);
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
    setlocale(LC_ALL, "");
    bindtextdomain("main", getenv("PWD"));
    textdomain ("main");

    int isRoman = 0;
    if (argc > 1) {
        if (strcmp(argv[1], "-r") == 0) {
            isRoman = 1;
        } else if (strcmp(argv[1], "--help") == 0) {
            printf("%s\n%s\n\t%s\n\t%s\n%s\n", _("A simple number guessing game"), _("Usage: main [-r, --help]"),
                   _("-r - use roman numerals"), _("--help - show this help"), _("ru and en locales are available"));
            return 0;
        }
    }

    int number_of_guesses = guess(1, 100, isRoman);

    const char *number_of_guesses_str = num_to_str(number_of_guesses, isRoman);
    printf("%s %s\n", _("Number of guesses"),  number_of_guesses_str);

    return 0;
}

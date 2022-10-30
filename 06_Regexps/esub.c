#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "regex.h"

#define MAX_ERROR_SIZE 200
#define MAX_MATCH_ARR_SIZE 100

int main(int argc, char** argv) {
    // region parse arguments
    if (argc != 4) {
        printf("Wrong number of arguments\n");
        printf("Usage: esub <string> <pattern> <replacement>\n");
        return 0;
    }

    char* string = argv[1];
    char* pattern = argv[2];
    char* replacement = argv[3];
    // endregion

    // region compile regexp
    regex_t regex;
    int result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        char *error_text = calloc(MAX_ERROR_SIZE, sizeof(*error_text));
        regerror(result, &regex, error_text, MAX_ERROR_SIZE);
        printf("Error compiling regex: %s\n", error_text);
        free(error_text);
        regfree(&regex);
        return 0;
    }
    // endregion

    // region match regexp
    regmatch_t match_arr[MAX_MATCH_ARR_SIZE];
    result = regexec(&regex, string, MAX_MATCH_ARR_SIZE, match_arr, 0);
    if (result == REG_NOMATCH) {
        printf("No match\n");
        regfree(&regex);
        return 0;
    } else if (result != 0) {
        char *error_text = calloc(MAX_ERROR_SIZE, sizeof(*error_text));
        regerror(result, &regex, error_text, MAX_ERROR_SIZE);
        printf("Error matching regex: %s\n", error_text);
        free(error_text);
        regfree(&regex);
        return 0;
    }
    // endregion

    // region replace matched string
    regoff_t match_start = match_arr[0].rm_so;
    regoff_t match_end = match_arr[0].rm_eo;
    regoff_t match_len = match_end - match_start;
    size_t replacement_len = strlen(replacement);
    size_t string_len = strlen(string);
    size_t new_string_len = string_len - match_len + replacement_len;
    char* new_string = calloc(new_string_len + 1, sizeof(*new_string));
    strncpy(new_string, string, match_start);
    strncpy(new_string + match_start, replacement, replacement_len);
    strncpy(new_string + match_start + replacement_len, string + match_end, string_len - match_end);
    printf("%s\n", new_string);
    // endregion

    free(new_string);
    regfree(&regex);

    return 0;
}

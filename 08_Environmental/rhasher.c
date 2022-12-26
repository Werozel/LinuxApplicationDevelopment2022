#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "rhash.h"

int main() {

    char *line = NULL;
    size_t len = 0;

    char *hashtype = NULL;
    char *string = NULL;
    while ((getline(&line, &len, stdin)) != -1) {

        hashtype = strtok(line, " ");
        string = strtok(strtok(NULL, " "), "\n");

        if (hashtype == NULL || string == NULL) {
            printf("Invalid input\n");
            continue;
        }

        printf("%s %s\n", hashtype, string);
    }

    free(line);
    free(hashtype);
    free(string);
    return 0;
}

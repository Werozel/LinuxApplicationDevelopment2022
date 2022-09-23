#include "stdio.h"
#include "stdlib.h"
#include "string.h"

const long STR_SIZE = 1000;

int main() {
    char* str = malloc((STR_SIZE + 1) * sizeof(char));
    fgets(str, STR_SIZE, stdin);

    int slen = strlen(str);
    if (slen > 0 && str[slen - 1] == '\n') {
        str[slen - 1] = '\0';
    }

    printf("Hello, %s!", str);

    free(str);
    return 0;
}

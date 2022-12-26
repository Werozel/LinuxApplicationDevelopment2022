#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "rhash.h"
#include "ctype.h"
#include "errno.h"
#include "config.h"

#ifdef READLINE
#include <readline/readline.h>
#endif

int main() {
    rhash_library_init();

    char *line = NULL;
    size_t len = 0;

    unsigned char *res_bytes = malloc(64 * sizeof(unsigned char));
    char *res_str = malloc(1000 * sizeof(char));

    char *hashtype_str = NULL;
    char *string = NULL;

#ifdef READLINE
    while ((line = readline(NULL))) {
#else
    while ((getline(&line, &len, stdin)) != -1) {
#endif

        hashtype_str = strtok(line, " ");
        string = strtok(strtok(NULL, " "), "\n");

        if (hashtype_str == NULL || string == NULL) {
            printf("Invalid input\n");
            continue;
        }

        int base = RHPR_HEX;
        if (hashtype_str[0] >= 'a' && hashtype_str[0] <= 'z') {
            base = RHPR_BASE64;
        }

        for (int i = 0; hashtype_str[i]; i++) {
            hashtype_str[i] = tolower(hashtype_str[i]);
        }

        int hashtype;
        if (strcmp(hashtype_str, "md5") == 0) {
            hashtype = RHASH_MD5;
        } else if (strcmp(hashtype_str, "sha1") == 0) {
            hashtype = RHASH_SHA1;
        } else if (strcmp(hashtype_str, "tth") == 0) {
            hashtype = RHASH_TTH;
        } else {
            printf("Invalid hash type\n");
            continue;
        }

        int isString = string[0] == '\"';

        int res;
        if (!isString) {
            res = rhash_file(hashtype, string, res_bytes);
        } else {
            res = rhash_msg(hashtype, string + 1, strlen(string + 1), res_bytes);
        }

        if (res < 0) {
            fprintf(stderr, "%s\n", strerror(errno));
            continue;
        }

        rhash_print_bytes(res_str, res_bytes, rhash_get_digest_size(hashtype), base);
        printf("%s\n", res_str);
    }

    free(res_bytes);
    free(res_str);
    return 0;
}

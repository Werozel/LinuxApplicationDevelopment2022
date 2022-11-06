#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


enum EXIT_CODES {
    OK = 0,
    ERROR_OPEN_FILE = 1,
    ERROR_WRITING_TO_FILE = 2,
    ERROR_CLOSING_FILE = 3,
    ERROR_REMOVING_FILE = 4,
};


void clean(FILE *first_file, char* first_filename, FILE *second_file, char* second_filename, enum EXIT_CODES exit_code) {
    if (first_file != NULL) {
        if (fclose(first_file) != 0) {
            exit(ERROR_CLOSING_FILE);
        }
    }
    if (second_file != NULL) {
        if (fclose(second_file) != 0) {
            exit(ERROR_CLOSING_FILE);
        }
        if (second_filename != NULL && remove(second_filename) != 0) {
            exit(ERROR_REMOVING_FILE);
        }
    }

    if (first_filename != NULL && remove(first_filename) != 0) {
        exit(ERROR_REMOVING_FILE);
    }

    exit(exit_code);
}


int main(int argc, char** argv) {

    // region parse arguments
    if (argc != 3) {
        printf("Wrong number of arguments\n");
    }

    char* first_filename = argv[1];
    char* second_filename = argv[2];
    // endregion

    // region open files
    FILE* first_file = fopen(first_filename, "r");
    if (first_file == NULL) {
        clean(NULL, NULL, NULL,  NULL, ERROR_OPEN_FILE);
    }

    FILE* second_file = fopen(second_filename, "w");
    if (second_file == NULL) {
        clean(first_file, NULL, NULL, NULL, ERROR_OPEN_FILE);
    }
    // endregion

    // region copy file
    int *c = malloc(sizeof(int));
    int second_fd = fileno(second_file);
    while ((*c = fgetc(first_file)) != EOF) {
        if (write(second_fd, c, 1) < 0) {
            clean(first_file, NULL, second_file, second_filename, ERROR_WRITING_TO_FILE);
        }
    }
    // endregion

    clean(first_file, first_filename, second_file, NULL, OK);
    return 0;
}

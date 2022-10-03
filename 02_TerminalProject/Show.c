#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LINES_COUNT 1000


struct LinesInfo {
    int lines_c;
    char** lines;
};


struct LinesInfo read_lines_from_file(char* file_name) {
    FILE* f = fopen(file_name, "r");
    if (f == NULL) {
        printf("Invalid file name\n");
        exit(1);
    }

    char** lines = malloc(MAX_LINES_COUNT * sizeof(char *));
    int lines_c = 0;
    char* line;
    size_t line_len;
    while (getline(&line, &line_len, f) != -1) {
        lines[lines_c] = malloc((strlen(line) + 1) * sizeof(char));
        strncpy(lines[lines_c++], line, strlen(line));
    }

    struct LinesInfo linesInfo;
    linesInfo.lines = lines;
    linesInfo.lines_c = lines_c;

    return linesInfo;
}


int main(int argc, char** argv) {
    if (argc < 2) {
        printf("No file to open!\n");
        return 1;
    }
    char* file_name = argv[1];

    struct LinesInfo linesInfo = read_lines_from_file(file_name);
    char** lines = linesInfo.lines;
    int lines_c = linesInfo.lines_c;

    for (int i = 0; i < lines_c; i++) {
        printf("%d: %s", i, lines[i]);
    }

    for (int i = 0; i < lines_c; i++) {
        free(lines[i]);
    }
    free(lines);

    return 0;
}

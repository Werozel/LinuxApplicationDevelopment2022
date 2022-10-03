#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>


#define MAX_LINES_COUNT 1000


struct LinesInfo {
    int lines_c;
    char** lines;
};


struct LinesInfo read_lines_from_file(const char* file_name) {
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


void render_window(WINDOW *win, const struct LinesInfo linesInfo, const int currLine) {
    if (linesInfo.lines_c  - currLine < LINES - 1) {
        return;
    }

    werase(win);
    wmove(win, 1, 0);

    for (int i = currLine; i < LINES - 1 + currLine; i++) {
        wprintw(win, " %.*s", COLS - 3, linesInfo.lines[i]);
    }

    box(win, 0, 0);
    wrefresh(win);
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

    initscr();
    printw(file_name);

    WINDOW *win = newwin(LINES - 1, COLS, 1, 0);
    refresh();

    keypad(win, TRUE);
    scrollok (win, TRUE);

    int currLine = 0;
    render_window(win, linesInfo, currLine);
    while (1) {
        int exiting = 0;
        switch (wgetch(win)) {
            case 27: // ESC
                exiting = 1;
                break;
            case 32: // Space
                ++currLine;
                render_window(win, linesInfo, currLine);
                break;
        }
        if (exiting) {
            break;
        }
    }

    wrefresh(win);

    getch();
    delwin(win);
    endwin();

    for (int i = 0; i < lines_c; i++) {
        free(lines[i]);
    }
    free(lines);

    return 0;
}

#include <stdio.h>
#include <ncurses.h>

#define DX 1

void showLine(WINDOW* win, FILE* f, int cols) {
    char c;
    for (int i = 0; i < cols; i++) {
        if ((c = fgetc(f)) != EOF ) {
            wprintw(win, "%c", c);
        }
        if (c == '\n') {
            break;
        }
    } 
}

void showPage(WINDOW* win, FILE* f, int cols, int rows) {
    for (int i = 0; i < rows; i++) {
        showLine(win, f, cols);
    }
}


void show(const char* filename, FILE* f) {
    WINDOW *win, *square;
    int c = 0;
    initscr();
    noecho();
    cbreak();
    int rows = LINES - 3 * DX;
    int cols = COLS - 3 * DX;
    fseek(f, 0, SEEK_END); // seek to end of file
    int size = ftell(f); // get current file pointer
    fseek(f, 0, SEEK_SET);
    printw("File name: %s; amount of characters: %d", filename, size);
    refresh();

    square = newwin(LINES - DX, COLS - DX, DX, DX);
    box(square, 0, 0);
    wrefresh(square);

    win = newwin(rows, cols, 2 * DX, 2 * DX);
    keypad(win, TRUE);
    scrollok (win, TRUE);

    showPage(win, f, cols, rows);
    do {
        if (c == 32) {
            showLine(win, f, cols);
            wrefresh(win);
        }
    } while((c = wgetch(win)) != 27);

    endwin();
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        printf("Usage: show filename\n");
        return 1;
    } else if (argc > 2) {
        printf("Too many arguments\n");
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("File '%s' can't be opened\n", argv[1]);
        return 1;
    }
    show(argv[1], f);
    fclose(f);
    return 0;
}
#include "cursed.h"
#include "game.h"

WINDOW *init_screen() {
    WINDOW *win = initscr();
    noecho();
    cbreak();
    keypad(win, TRUE);
    return (win);
}

void end_screen(int code) {
    endwin();

    // clear_memory();

    exit(code);
}

int main() {
    WINDOW *win = init_screen();

    int val = gameloop(win);

    end_screen(val);
}
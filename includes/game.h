#ifndef GAME_H_
# define GAME_H_

# include <curses.h>

int gameloop(WINDOW *win);

typedef struct  board_t {
    char **table;
}               board_s;

#endif
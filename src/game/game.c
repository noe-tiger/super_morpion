#include "cursed.h"
#include "game.h"
#include "memory.h"

void move_curs(int ch, const int board_x, const int board_y) {
    const int x_size = 4;
    const int y_size = 2;
    static int x = 1;
    static int y = 1;

    // need to be re done !!!
    if (ch == KEY_LEFT && x > 0) {
        x -= 1;
    } else if (ch == KEY_RIGHT && x < 2) {
        x += 1;
    } else if (ch == KEY_DOWN && y < 2) {
        y += 1;
    } else if (ch == KEY_UP && y > 0) {
        y -= 1;
    }
    move((2 + board_y * 7) + (y * y_size),
         (3 + board_x * 13) + (x * x_size));
}

void print_basic_board() {
    int boul = 0;
    for (int i = 0; i < 23; i++) {
        if (i % 7 == 0 || (i - 1) % 7 == 0) {
            mvprintw(i, 0, "-----------------------------------------");
            boul = 0;
        } else {
            if (!boul) {
                boul = 1;
                mvprintw(i, 0, "||   |   |   ||   |   |   ||   |   |   ||");
            } else
            {
                boul = 0;
                mvprintw(i, 0, "||--- --- ---||--- --- ---||--- --- ---||");
            }
        }
    }
}

int update_board(board_s **board, int *board_x, int *board_y, int ch, WINDOW *win) {
    const int x_size = 4;
    const int y_size = 2;
    static char player = 0;

    if (ch == '\n') {
        int x, y;
        getyx(win, y, x);

        if (mvinch(y, x) != ' ') {
            return (0);
        }

        char move = (player ? 'x' : 'o');
        int new_x = (x - (3 + *board_x * 13)) / x_size;
        int new_y = (y - (2 + *board_y * 7)) / y_size;
        mvprintw(y, x, "%c", move);
        player = (player ? 0 : 1);
        board[*board_y][*board_x].table[new_y][new_x] = move;
        *board_x = new_x;
        *board_y = new_y;
	return (1);
    }
    return (0);
}

int check_single_case(board_s *board) {
    board = board;
    // check horizontal
    for (int i = 0; i < 3; i++) {
        if (board->table[i][0] == board->table[i][1] &&
            board->table[i][0] == board->table[i][2] &&
            board->table[i][0] != ' ')
            return (1);
    }
    // check vertical
    for (int i = 0; i < 3; i++) {
        if (board->table[0][i] == board->table[1][i] && 
            board->table[0][i] == board->table[2][i] && 
            board->table[0][i] != ' ')
            return (1);
    }
    // check diagonal
    if (board->table[0][0] == board->table[1][1] &&
        board->table[0][0] == board->table[2][2] &&
        board->table[1][1] != ' ')
        return (1);
    if (board->table[2][0] == board->table[1][1] &&
        board->table[2][0] == board->table[0][2] &&
        board->table[1][1] != ' ')
        return (1);
    return (0);
}

int check_win(board_s **board) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (check_single_case(&board[i][j]) != 0) {
                return (1);
            }
        }
    }
    return (0);
}

int print_game(WINDOW *win, board_s **board) {
    char player = 0;
    int ch = 0;
    int board_x = 1;
    int board_y = 1;

    print_basic_board();
    mvprintw(24, 4, "player to play : %c", (player ? 'o' : 'x'));
    move_curs(ch, board_x, board_y);
    while (ch != 27) {
        ch = wgetch(win);
        if (update_board(board, &board_x, &board_y, ch, win)) {
            player = (player ? 0 : 1);
        }
        mvprintw(24, 4, "player to play : %c", (player ? 'o' : 'x'));
        move_curs(ch, board_x, board_y);
        if (check_win(board) != 0) {
            break ;
        }
    }
    free_board(board);
    return(0);
}

int gameloop(WINDOW *win) {
    return (print_game(win, get_game_board()));
}

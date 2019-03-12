#include "cursed.h"
#include "game.h"

static void free_table(board_s *board) {
    for (int i = 0; i < 3; i++) {
        free(board->table[i]);
    }
    free(board->table);
}

void free_board(board_s **board) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            free_table(&board[i][j]);
        }
        free(board[i]);
    }
    free(board);
}

static int get_single_board(board_s *board) {
    board->table = malloc(sizeof(char *) * 3);
    if (!board->table)
        return (-1);
    for (int i = 0; i < 3; i++) {
        board->table[i] = malloc(sizeof(char) * 3);
        if (!board->table[i]) {
            while (i >= 0) {
                free(board->table[i--]);
            }
            free(board->table);
            return (-1);
        }
        for (int j = 0; j < 3; j++) {
            board->table[i][j] = ' ';
        }
    }
    return (0);
}

board_s **get_game_board() {
    board_s **board = malloc(sizeof(board_s *) * 3);

    if (!board) {
        return (NULL);
    }
    for (int i = 0; i < 3; i++) {
        board[i] = malloc(sizeof(board_s) * 3);
        if (!board[i]) {
            while (i >= 0) {
                free(board[i--]);
            }
            free(board);
            return (NULL);
        }
        for (int j = 0; j < 3; j++) {
            if (get_single_board(&board[i][j]) == -1) {
                while (i >= 0) {
                    while (j >= 0) {
                        free_table(&board[i][j--]);
                    }
                    free(board[i]);
                    i--;
                    j = 2;
                }
                free(board);
                return (NULL);
            }
        }
    }
    return (board);
}

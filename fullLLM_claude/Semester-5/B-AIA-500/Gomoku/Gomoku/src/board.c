/*
** EPITECH PROJECT, 2024
** Gomoku AI
** File description:
** Board representation and basic operations
*/

#include "gomoku.h"

void init_board(game_board_t *board)
{
    int i, j;
    
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            board->board[i][j] = EMPTY;
        }
    }
    board->move_count = 0;
    board->last_move.x = -1;
    board->last_move.y = -1;
    board->current_player = PLAYER_AI;
}

void copy_board(game_board_t *dest, const game_board_t *src)
{
    int i, j;
    
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            dest->board[i][j] = src->board[i][j];
        }
    }
    dest->move_count = src->move_count;
    dest->last_move = src->last_move;
    dest->current_player = src->current_player;
}

int is_valid_move(const game_board_t *board, int x, int y)
{
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
        return 0;
    }
    return board->board[y][x] == (int)EMPTY;
}

void make_move(game_board_t *board, int x, int y, player_t player)
{
    if (is_valid_move(board, x, y)) {
        board->board[y][x] = player;
        board->last_move.x = x;
        board->last_move.y = y;
        board->move_count++;
        board->current_player = get_opponent(player);
    }
}

void undo_move(game_board_t *board, int x, int y)
{
    if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
        board->board[y][x] = EMPTY;
        board->move_count--;
        board->current_player = get_opponent(board->current_player);
    }
}

void print_board(const game_board_t *board)
{
    int i, j;
    
    fprintf(stderr, "   ");
    for (i = 0; i < BOARD_SIZE; i++) {
        fprintf(stderr, "%2d ", i);
    }
    fprintf(stderr, "\n");
    
    for (i = 0; i < BOARD_SIZE; i++) {
        fprintf(stderr, "%2d ", i);
        for (j = 0; j < BOARD_SIZE; j++) {
            if (board->board[i][j] == (int)EMPTY) {
                fprintf(stderr, " . ");
            } else if (board->board[i][j] == (int)PLAYER_AI) {
                fprintf(stderr, " X ");
            } else {
                fprintf(stderr, " O ");
            }
        }
        fprintf(stderr, "\n");
    }
    fprintf(stderr, "\n");
}
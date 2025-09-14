/*
** EPITECH PROJECT, 2024
** Gomoku AI
** File description:
** Game logic and win condition checking
*/

#include "gomoku.h"

int count_consecutive(const game_board_t *board, int x, int y, int dx, int dy, player_t player)
{
    int count = 0;
    int nx = x;
    int ny = y;
    
    // Count in positive direction
    while (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE && 
           board->board[ny][nx] == (int)player) {
        count++;
        nx += dx;
        ny += dy;
    }
    
    // Count in negative direction (excluding the starting position)
    nx = x - dx;
    ny = y - dy;
    while (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE && 
           board->board[ny][nx] == (int)player) {
        count++;
        nx -= dx;
        ny -= dy;
    }
    
    return count;
}

int check_win(const game_board_t *board, int x, int y, player_t player)
{
    // Check all four directions: horizontal, vertical, and two diagonals
    int directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};
    int i;
    
    for (i = 0; i < 4; i++) {
        int dx = directions[i][0];
        int dy = directions[i][1];
        
        if (count_consecutive(board, x, y, dx, dy, player) >= WIN_LENGTH) {
            return 1;
        }
    }
    
    return 0;
}

int is_game_over(const game_board_t *board)
{
    int i, j;
    
    // Check if board is full
    if (board->move_count >= MAX_MOVES) {
        return 1;
    }
    
    // Check for wins
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (board->board[i][j] != (int)EMPTY) {
                if (check_win(board, j, i, board->board[i][j])) {
                    return 1;
                }
            }
        }
    }
    
    return 0;
}

player_t get_opponent(player_t player)
{
    return (player == PLAYER_AI) ? PLAYER_OPPONENT : PLAYER_AI;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int min(int a, int b)
{
    return (a < b) ? a : b;
}
#include "setting_up.h"

board_t *generate_board(int size, char const *pattern)
{
    board_t *board;
    int pattern_len = my_strlen(pattern);
    int i, j;
    
    if (size <= 0 || !pattern || pattern_len == 0)
        return 0;
    
    board = malloc(sizeof(board_t));
    if (!board)
        return 0;
    
    board->rows = size;
    board->cols = pattern_len;
    board->board = malloc(size * sizeof(char *));
    
    if (!board->board) {
        free(board);
        return 0;
    }
    
    for (i = 0; i < size; i++) {
        board->board[i] = malloc(pattern_len + 1);
        if (!board->board[i]) {
            for (j = 0; j < i; j++)
                free(board->board[j]);
            free(board->board);
            free(board);
            return 0;
        }
        
        for (j = 0; j < pattern_len; j++) {
            board->board[i][j] = pattern[(i * pattern_len + j) % pattern_len];
        }
        board->board[i][pattern_len] = '\0';
    }
    
    return board;
}
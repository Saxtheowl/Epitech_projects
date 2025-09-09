#include "setting_up.h"

static int min3(int a, int b, int c)
{
    int min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    return min;
}

square_t find_largest_square(board_t *board)
{
    int **dp;
    square_t result = {0, 0, 0};
    int i, j;
    
    if (!board || board->rows == 0 || board->cols == 0)
        return result;
    
    dp = malloc(board->rows * sizeof(int *));
    if (!dp)
        return result;
    
    for (i = 0; i < board->rows; i++) {
        dp[i] = malloc(board->cols * sizeof(int));
        if (!dp[i]) {
            for (j = 0; j < i; j++)
                free(dp[j]);
            free(dp);
            return result;
        }
    }
    
    for (i = 0; i < board->rows; i++) {
        for (j = 0; j < board->cols; j++) {
            if (board->board[i][j] == 'o') {
                dp[i][j] = 0;
            } else if (i == 0 || j == 0) {
                dp[i][j] = 1;
            } else {
                dp[i][j] = min3(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1;
            }
            
            if (dp[i][j] > result.size) {
                result.size = dp[i][j];
                result.row = i - result.size + 1;
                result.col = j - result.size + 1;
            } else if (dp[i][j] == result.size && dp[i][j] > 0) {
                int new_row = i - dp[i][j] + 1;
                int new_col = j - dp[i][j] + 1;
                if (new_row < result.row || (new_row == result.row && new_col < result.col)) {
                    result.row = new_row;
                    result.col = new_col;
                }
            }
        }
    }
    
    for (i = 0; i < board->rows; i++)
        free(dp[i]);
    free(dp);
    
    return result;
}

void place_square_on_board(board_t *board, square_t square)
{
    int i, j;
    
    if (!board || square.size == 0)
        return;
    
    for (i = square.row; i < square.row + square.size; i++) {
        for (j = square.col; j < square.col + square.size; j++) {
            if (i < board->rows && j < board->cols && board->board[i][j] == '.') {
                board->board[i][j] = 'x';
            }
        }
    }
}

void print_board(board_t *board)
{
    int i;
    
    if (!board)
        return;
    
    for (i = 0; i < board->rows; i++) {
        my_putstr(board->board[i]);
        my_putchar('\n');
    }
}

void free_board(board_t *board)
{
    int i;
    
    if (!board)
        return;
    
    if (board->board) {
        for (i = 0; i < board->rows; i++) {
            if (board->board[i])
                free(board->board[i]);
        }
        free(board->board);
    }
    
    free(board);
}
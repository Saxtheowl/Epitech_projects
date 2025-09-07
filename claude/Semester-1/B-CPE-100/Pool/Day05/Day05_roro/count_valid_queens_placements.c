int is_safe(int board[], int row, int col, int n)
{
    int i;

    for (i = 0; i < row; i++) {
        if (board[i] == col)
            return 0;
        if (board[i] - i == col - row)
            return 0;
        if (board[i] + i == col + row)
            return 0;
    }
    return 1;
}

int solve_nqueens(int board[], int row, int n)
{
    int col;
    int count = 0;

    if (row == n)
        return 1;

    for (col = 0; col < n; col++) {
        if (is_safe(board, row, col, n)) {
            board[row] = col;
            count += solve_nqueens(board, row + 1, n);
        }
    }
    return count;
}

int count_valid_queens_placements(int n)
{
    int board[20];
    int i;

    if (n <= 0)
        return 0;

    for (i = 0; i < n; i++) {
        board[i] = -1;
    }

    return solve_nqueens(board, 0, n);
}
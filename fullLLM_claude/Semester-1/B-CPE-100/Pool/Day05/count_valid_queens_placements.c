int is_safe(int *board, int row, int col, int n)
{
    int i = 0;
    int j = 0;
    
    while (i < row) {
        if (board[i] == col) {
            return (0);
        }
        i++;
    }
    
    i = 0;
    while (i < row) {
        if (board[i] == col - (row - i) || board[i] == col + (row - i)) {
            return (0);
        }
        i++;
    }
    
    return (1);
}

int solve_queens(int *board, int row, int n)
{
    int col = 0;
    int count = 0;
    
    if (row == n) {
        return (1);
    }
    
    while (col < n) {
        if (is_safe(board, row, col, n)) {
            board[row] = col;
            count += solve_queens(board, row + 1, n);
        }
        col++;
    }
    
    return (count);
}

int count_valid_queens_placements(int n)
{
    int board[20];
    int i = 0;
    
    if (n <= 0) {
        return (0);
    }
    
    while (i < n) {
        board[i] = -1;
        i++;
    }
    
    return (solve_queens(board, 0, n));
}
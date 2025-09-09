#include "setting_up.h"

char *read_file_content(char const *filename, int *size)
{
    int fd = open(filename, O_RDONLY);
    struct stat st;
    char *content;
    int bytes_read;
    
    if (fd == -1 || stat(filename, &st) == -1)
        return 0;
    
    *size = st.st_size;
    content = malloc(*size + 1);
    if (!content) {
        close(fd);
        return 0;
    }
    
    bytes_read = read(fd, content, *size);
    close(fd);
    
    if (bytes_read != *size) {
        free(content);
        return 0;
    }
    
    content[*size] = '\0';
    return content;
}

int is_valid_file(char const *content, int size)
{
    int i = 0;
    int line_len = 0;
    int expected_line_len = -1;
    
    if (size == 0)
        return 0;
    
    while (i < size && content[i] != '\n') {
        if (content[i] < '0' || content[i] > '9')
            return 0;
        i++;
    }
    
    if (i == size || content[i] != '\n')
        return 0;
    
    i++;
    
    while (i < size) {
        line_len = 0;
        while (i < size && content[i] != '\n') {
            if (content[i] != '.' && content[i] != 'o')
                return 0;
            line_len++;
            i++;
        }
        
        if (expected_line_len == -1)
            expected_line_len = line_len;
        else if (line_len != expected_line_len)
            return 0;
        
        if (i < size)
            i++;
    }
    
    return expected_line_len > 0;
}

static int count_actual_lines(char const *content, int size)
{
    int count = 0;
    int i = 0;
    int line_has_content = 0;
    
    while (i < size && content[i] != '\n')
        i++;
    i++;
    
    while (i < size) {
        line_has_content = 0;
        while (i < size && content[i] != '\n') {
            line_has_content = 1;
            i++;
        }
        if (line_has_content)
            count++;
        if (i < size)
            i++;
    }
    
    return count;
}

board_t *read_board_from_file(char const *filename)
{
    char *content;
    int size;
    board_t *board;
    int i = 0, j, row = 0;
    int actual_lines;
    
    content = read_file_content(filename, &size);
    if (!content || !is_valid_file(content, size)) {
        if (content)
            free(content);
        return 0;
    }
    
    board = malloc(sizeof(board_t));
    if (!board) {
        free(content);
        return 0;
    }
    
    board->rows = 0;
    while (content[i] != '\n') {
        board->rows = board->rows * 10 + (content[i] - '0');
        i++;
    }
    i++;
    
    actual_lines = count_actual_lines(content, size);
    if (actual_lines != board->rows) {
        free(board);
        free(content);
        return 0;
    }
    
    board->cols = 0;
    while (i < size && content[i] != '\n') {
        board->cols++;
        i++;
    }
    
    board->board = malloc(board->rows * sizeof(char *));
    if (!board->board) {
        free(board);
        free(content);
        return 0;
    }
    
    i = 0;
    while (content[i] != '\n')
        i++;
    i++;
    
    for (row = 0; row < board->rows; row++) {
        board->board[row] = malloc(board->cols + 1);
        if (!board->board[row]) {
            for (j = 0; j < row; j++)
                free(board->board[j]);
            free(board->board);
            free(board);
            free(content);
            return 0;
        }
        
        for (j = 0; j < board->cols; j++) {
            board->board[row][j] = content[i];
            i++;
        }
        board->board[row][j] = '\0';
        if (i < size && content[i] == '\n')
            i++;
    }
    
    free(content);
    return board;
}
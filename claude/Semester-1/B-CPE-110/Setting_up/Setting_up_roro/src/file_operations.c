/*
** EPITECH PROJECT, 2025
** Setting_up
** File description:
** file reading and parsing functions
*/

#include "../include/setting_up.h"

int read_file_to_string(char *filename, char **content)
{
    struct stat st;
    int fd;
    char *buffer;
    int size;

    if (stat(filename, &st) == -1)
        return -1;
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return -1;
    buffer = malloc(st.st_size + 1);
    if (buffer == NULL) {
        close(fd);
        return -1;
    }
    size = read(fd, buffer, st.st_size);
    if (size == -1) {
        free(buffer);
        close(fd);
        return -1;
    }
    buffer[size] = '\0';
    close(fd);
    *content = buffer;
    return 0;
}

static int count_lines(char *content)
{
    int lines = 0;
    int i = 0;

    if (content == NULL || content[0] == '\0')
        return 0;
    while (content[i]) {
        if (content[i] == '\n')
            lines++;
        i++;
    }
    if (i > 0 && content[i - 1] != '\n')
        lines++;
    return lines;
}

static int get_line_length(char *content, int start)
{
    int len = 0;

    while (content[start + len] && content[start + len] != '\n')
        len++;
    return len;
}

board_t *parse_board_from_file(char *content)
{
    board_t *board;
    int num_lines = my_atoi(content);
    int i = 0;
    int line_start = 0;
    int j;

    if (num_lines <= 0)
        return NULL;
    while (content[i] && content[i] != '\n')
        i++;
    if (content[i] == '\n')
        i++;
    line_start = i;
    if (count_lines(content + line_start) != num_lines)
        return NULL;
    board = new_board(num_lines, get_line_length(content, line_start));
    if (board == NULL)
        return NULL;
    for (int row = 0; row < num_lines; row++) {
        j = 0;
        while (content[i] && content[i] != '\n' && j < board->cols) {
            board->grid[row][j] = content[i];
            j++;
            i++;
        }
        if (j != board->cols) {
            free_board(board);
            return NULL;
        }
        if (content[i] == '\n')
            i++;
    }
    return board;
}
/*
** EPITECH PROJECT, 2024
** BSQ
** File description:
** File reading and parsing operations
*/

#include "../include/bsq.h"

char *read_file_content(const char *filepath, size_t *size)
{
    int fd;
    struct stat st;
    char *content;
    ssize_t bytes_read;

    fd = open(filepath, O_RDONLY);
    if (fd == -1)
        return NULL;

    if (stat(filepath, &st) == -1 || st.st_size == 0) {
        close(fd);
        return NULL;
    }

    *size = st.st_size;
    content = malloc(*size + 1);
    if (!content) {
        close(fd);
        return NULL;
    }

    bytes_read = read(fd, content, *size);
    close(fd);

    if (bytes_read != (ssize_t)*size) {
        free(content);
        return NULL;
    }

    content[*size] = '\0';
    return content;
}

int parse_board_header(const char *content, size_t *num_lines, size_t *offset)
{
    size_t i = 0;
    char num_str[32];
    size_t num_idx = 0;

    while (content[i] && content[i] != '\n' && i < 31) {
        if (content[i] < '0' || content[i] > '9')
            return -1;
        num_str[num_idx++] = content[i];
        i++;
    }

    if (content[i] != '\n' || num_idx == 0)
        return -1;

    num_str[num_idx] = '\0';
    *num_lines = my_atoi(num_str);
    *offset = i + 1;

    return (*num_lines > 0) ? 0 : -1;
}
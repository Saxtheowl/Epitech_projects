/*
** EPITECH PROJECT, 2024
** file_operations.c
** File description:
** File reading operations for BSQ
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "../include/bsq.h"

int read_file(char const *filename, char **content)
{
    int fd;
    struct stat file_stat;
    int size;

    if (filename == NULL || content == NULL)
        return -1;
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return -1;
    if (stat(filename, &file_stat) == -1) {
        close(fd);
        return -1;
    }
    size = file_stat.st_size;
    *content = malloc(size + 1);
    if (*content == NULL) {
        close(fd);
        return -1;
    }
    if (read(fd, *content, size) != size) {
        close(fd);
        free(*content);
        return -1;
    }
    (*content)[size] = '\0';
    close(fd);
    return size;
}
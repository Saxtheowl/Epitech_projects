/*
** EPITECH PROJECT, 2024
** file_operations.c
** File description:
** File reading and writing operations for compression programs
*/

#include "compression.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

char *read_file_content(const char *filename, size_t *file_size)
{
    int fd;
    struct stat st;
    char *content;
    ssize_t bytes_read;

    if (!filename || !file_size)
        return NULL;
    
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return NULL;
    
    if (fstat(fd, &st) == -1) {
        close(fd);
        return NULL;
    }
    
    *file_size = st.st_size;
    content = malloc(*file_size + 1);
    if (!content) {
        close(fd);
        return NULL;
    }
    
    bytes_read = read(fd, content, *file_size);
    close(fd);
    
    if (bytes_read != (ssize_t)*file_size) {
        free(content);
        return NULL;
    }
    
    content[*file_size] = '\0';
    return content;
}

int write_compressed_data(const char *data, size_t size)
{
    ssize_t bytes_written;
    
    if (!data || size == 0)
        return -1;
    
    bytes_written = write(STDOUT_FILENO, data, size);
    return (bytes_written == (ssize_t)size) ? 0 : -1;
}

int write_decompressed_data(const char *data, size_t size)
{
    ssize_t bytes_written;
    
    if (!data || size == 0)
        return -1;
    
    bytes_written = write(STDOUT_FILENO, data, size);
    return (bytes_written == (ssize_t)size) ? 0 : -1;
}
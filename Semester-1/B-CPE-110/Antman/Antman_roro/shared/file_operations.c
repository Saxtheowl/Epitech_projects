/*
** EPITECH PROJECT, 2024
** Antman
** File description:
** File operations implementation
*/

#include "compression.h"

buffer_t *create_buffer(void)
{
    buffer_t *buffer = malloc(sizeof(buffer_t));
    
    if (!buffer)
        return NULL;
    
    buffer->data = malloc(BUFFER_SIZE);
    if (!buffer->data) {
        free(buffer);
        return NULL;
    }
    
    buffer->size = 0;
    buffer->capacity = BUFFER_SIZE;
    
    return buffer;
}

void free_buffer(buffer_t *buffer)
{
    if (!buffer)
        return;
    
    if (buffer->data)
        free(buffer->data);
    free(buffer);
}

void append_to_buffer(buffer_t *buffer, char *data, size_t len)
{
    char *new_data;
    
    if (!buffer || !data)
        return;
    
    if (buffer->size + len >= buffer->capacity) {
        buffer->capacity = (buffer->size + len) * 2;
        new_data = malloc(buffer->capacity);
        if (!new_data)
            return;
        
        for (size_t i = 0; i < buffer->size; i++)
            new_data[i] = buffer->data[i];
        
        free(buffer->data);
        buffer->data = new_data;
    }
    
    for (size_t i = 0; i < len; i++)
        buffer->data[buffer->size + i] = data[i];
    
    buffer->size += len;
}

void append_char_to_buffer(buffer_t *buffer, char c)
{
    append_to_buffer(buffer, &c, 1);
}

buffer_t *read_file(char *filename)
{
    int fd;
    buffer_t *buffer;
    char read_buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    
    if (!filename)
        return NULL;
    
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return NULL;
    
    buffer = create_buffer();
    if (!buffer) {
        close(fd);
        return NULL;
    }
    
    while ((bytes_read = read(fd, read_buffer, BUFFER_SIZE)) > 0) {
        append_to_buffer(buffer, read_buffer, bytes_read);
    }
    
    close(fd);
    
    if (bytes_read == -1) {
        free_buffer(buffer);
        return NULL;
    }
    
    return buffer;
}

void write_buffer(buffer_t *buffer)
{
    if (!buffer || !buffer->data)
        return;
    
    write(1, buffer->data, buffer->size);
}
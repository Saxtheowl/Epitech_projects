#include "common.h"

buffer_t *buffer_create(size_t initial_capacity)
{
    buffer_t *buffer = malloc(sizeof(buffer_t));
    if (!buffer)
        return NULL;
    
    buffer->data = malloc(initial_capacity);
    if (!buffer->data) {
        free(buffer);
        return NULL;
    }
    
    buffer->size = 0;
    buffer->capacity = initial_capacity;
    return buffer;
}

void buffer_free(buffer_t *buffer)
{
    if (!buffer)
        return;
    
    if (buffer->data)
        free(buffer->data);
    free(buffer);
}

int buffer_append(buffer_t *buffer, const char *data, size_t size)
{
    if (!buffer || !data)
        return -1;
    
    if (buffer->size + size > buffer->capacity) {
        size_t new_capacity = (buffer->size + size) * 2;
        char *new_data = malloc(new_capacity);
        if (!new_data)
            return -1;
        
        for (size_t i = 0; i < buffer->size; i++)
            new_data[i] = buffer->data[i];
        
        free(buffer->data);
        buffer->data = new_data;
        buffer->capacity = new_capacity;
    }
    
    for (size_t i = 0; i < size; i++)
        buffer->data[buffer->size + i] = data[i];
    
    buffer->size += size;
    return 0;
}

int buffer_append_char(buffer_t *buffer, char c)
{
    return buffer_append(buffer, &c, 1);
}

char *read_file(const char *filename, size_t *file_size)
{
    int fd;
    struct stat st;
    char *buffer;
    ssize_t bytes_read;
    
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return NULL;
    
    if (stat(filename, &st) == -1) {
        close(fd);
        return NULL;
    }
    
    *file_size = st.st_size;
    buffer = malloc(*file_size);
    if (!buffer) {
        close(fd);
        return NULL;
    }
    
    bytes_read = read(fd, buffer, *file_size);
    close(fd);
    
    if (bytes_read != (ssize_t)*file_size) {
        free(buffer);
        return NULL;
    }
    
    return buffer;
}

int write_data(const char *data, size_t size)
{
    ssize_t written = 0;
    ssize_t result;
    
    while (written < (ssize_t)size) {
        result = write(STDOUT_FILENO, data + written, size - written);
        if (result == -1)
            return -1;
        written += result;
    }
    
    return 0;
}
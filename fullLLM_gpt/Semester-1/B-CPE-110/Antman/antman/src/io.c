#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "../include/antman.h"

static void copy_bytes(char *dst, const char *src, size_t len)
{
    for (size_t i = 0; i < len; ++i)
        dst[i] = src[i];
}

int write_all(int fd, const char *buf, size_t len)
{
    size_t off = 0;
    while (off < len) {
        ssize_t w = write(fd, buf + off, len - off);
        if (w <= 0)
            return -1;
        off += (size_t)w;
    }
    return 0;
}

char *read_entire_file(const char *path, size_t *out_len)
{
    int fd = open(path, O_RDONLY);
    if (fd < 0)
        return NULL;
    size_t cap = 4096;
    size_t len = 0;
    char *buffer = malloc(cap + 1);
    if (!buffer) {
        close(fd);
        return NULL;
    }
    while (1) {
        if (len == cap) {
            size_t new_cap = cap * 2;
            char *nb = malloc(new_cap + 1);
            if (!nb) {
                free(buffer);
                close(fd);
                return NULL;
            }
            copy_bytes(nb, buffer, len);
            free(buffer);
            buffer = nb;
            cap = new_cap;
        }
        ssize_t r = read(fd, buffer + len, cap - len);
        if (r < 0) {
            free(buffer);
            close(fd);
            return NULL;
        }
        if (r == 0)
            break;
        len += (size_t)r;
    }
    close(fd);
    buffer[len] = '\0';
    if (out_len)
        *out_len = len;
    return buffer;
}

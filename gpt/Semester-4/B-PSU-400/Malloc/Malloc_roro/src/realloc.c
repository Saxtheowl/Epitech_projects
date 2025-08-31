/*
** EPITECH PROJECT, 2025
** Malloc
** File description:
**   realloc and reallocarray
*/

#include <string.h>
#include "mmalloc.h"

void *realloc(void *ptr, size_t size)
{
    block_t *b = NULL;
    void *n = NULL;
    size_t cpy = 0;

    if (!ptr)
        return malloc(size);
    if (size == 0) {
        free(ptr);
        return NULL;
    }
    b = (block_t *)((char *)ptr - HEADER_SIZE);
    if (b->size >= size)
        return ptr;
    n = malloc(size);
    if (!n)
        return NULL;
    cpy = b->size < size ? b->size : size;
    memcpy(n, ptr, cpy);
    free(ptr);
    return n;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    if (nmemb != 0 && size > (size_t)-1 / nmemb)
        return NULL;
    return realloc(ptr, nmemb * size);
}


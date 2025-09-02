/*
** EPITECH PROJECT, 2025
** Malloc
** File description:
** realloc and reallocarray functions implementation
*/

#include "my_malloc.h"
#include <string.h>
#include <stdint.h>

void *realloc(void *ptr, size_t size)
{
    block_t *block;
    void *new_ptr;
    size_t copy_size;

    if (!ptr)
        return malloc(size);

    if (size == 0) {
        free(ptr);
        return NULL;
    }

    if (!is_valid_ptr(ptr))
        return NULL;

    block = get_block_from_ptr(ptr);
    
    if (block->size >= align_size(size))
        return ptr;

    new_ptr = malloc(size);
    if (!new_ptr)
        return NULL;

    copy_size = (block->size < size) ? block->size : size;
    memcpy(new_ptr, ptr, copy_size);
    free(ptr);

    return new_ptr;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    size_t total_size;

    if (nmemb == 0 || size == 0) {
        free(ptr);
        return NULL;
    }

    if (nmemb > SIZE_MAX / size)
        return NULL;

    total_size = nmemb * size;
    return realloc(ptr, total_size);
}
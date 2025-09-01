/*
** EPITECH PROJECT, 2025
** Malloc
** File description:
** realloc implementation
*/

#include "malloc.h"

static void *my_memcpy(void *dest, const void *src, size_t n)
{
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    
    while (n--)
        *d++ = *s++;
    return dest;
}

void *realloc(void *ptr, size_t size)
{
    if (!ptr)
        return malloc(size);
    
    if (size == 0) {
        free(ptr);
        return NULL;
    }
    
    block_t *block = (block_t *)((char *)ptr - sizeof(block_t));
    
    if (block < (block_t *)heap_start || 
        (char *)block >= (char *)sbrk(0))
        return NULL;
    
    size = align_size(size);
    
    if (block->size >= size) {
        split_block(block, size);
        return ptr;
    }
    
    void *new_ptr = malloc(size);
    if (!new_ptr)
        return NULL;
    
    size_t copy_size = block->size < size ? block->size : size;
    my_memcpy(new_ptr, ptr, copy_size);
    free(ptr);
    
    return new_ptr;
}
/*
** EPITECH PROJECT, 2025
** Malloc
** File description:
** malloc implementation using brk/sbrk
*/

#include "malloc.h"

void *malloc(size_t size)
{
    if (size == 0)
        return NULL;
    
    size = align_size(size);
    block_t *block = find_best_fit(size);
    
    if (!block) {
        block = expand_heap(size);
        if (!block)
            return NULL;
    }
    
    block->free = 0;
    split_block(block, size);
    
    return (void *)((char *)block + sizeof(block_t));
}
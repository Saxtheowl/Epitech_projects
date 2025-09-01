/*
** EPITECH PROJECT, 2025
** Malloc
** File description:
** free implementation
*/

#include "malloc.h"

void free(void *ptr)
{
    if (!ptr)
        return;
    
    block_t *block = (block_t *)((char *)ptr - sizeof(block_t));
    
    if (block < (block_t *)heap_start || 
        (char *)block >= (char *)sbrk(0))
        return;
    
    block->free = 1;
    merge_blocks(block);
}
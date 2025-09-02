/*
** EPITECH PROJECT, 2025
** Malloc
** File description:
** Utility functions
*/

#include "my_malloc.h"

void *get_user_ptr(block_t *block)
{
    if (!block)
        return NULL;
    return (char *)block + sizeof(block_t);
}

block_t *get_block_from_ptr(void *ptr)
{
    if (!ptr)
        return NULL;
    return (block_t *)((char *)ptr - sizeof(block_t));
}

int is_valid_ptr(void *ptr)
{
    block_t *block;

    if (!ptr || !g_heap.start)
        return 0;
    
    if ((char *)ptr < (char *)g_heap.start + sizeof(block_t) || ptr >= g_heap.end)
        return 0;
    
    block = get_block_from_ptr(ptr);
    
    if ((char *)block < (char *)g_heap.start || 
        (char *)block + sizeof(block_t) > (char *)g_heap.end)
        return 0;
    
    if (block->is_free)
        return 0;
    
    return 1;
}
/*
** EPITECH PROJECT, 2025
** Malloc
** File description:
** Block management functions
*/

#include "my_malloc.h"

block_t *find_best_fit(size_t size)
{
    block_t *current = g_heap.free_list;
    block_t *best_fit = NULL;
    size_t aligned_size = align_size(size);

    while (current) {
        if (current->is_free && current->size >= aligned_size) {
            if (!best_fit || current->size < best_fit->size)
                best_fit = current;
        }
        current = current->next;
    }
    return best_fit;
}

block_t *split_block(block_t *block, size_t size)
{
    block_t *new_block;
    size_t aligned_size = align_size(size);

    if (block->size < aligned_size + sizeof(block_t) + MIN_BLOCK_SIZE)
        return block;

    new_block = (block_t *)((char *)block + sizeof(block_t) + aligned_size);
    new_block->size = block->size - aligned_size - sizeof(block_t);
    new_block->is_free = 1;
    new_block->next = NULL;
    new_block->prev = NULL;

    block->size = aligned_size;
    add_to_free_list(new_block);
    return block;
}

void merge_free_blocks(block_t *block)
{
    block_t *current = g_heap.free_list;
    block_t *next_block;

    (void)block;
    while (current) {
        next_block = (block_t *)((char *)current + sizeof(block_t) + current->size);
        
        if ((char *)next_block < (char *)g_heap.end && 
            next_block->is_free &&
            (char *)current + sizeof(block_t) + current->size == (char *)next_block) {
            current->size += sizeof(block_t) + next_block->size;
            remove_from_free_list(next_block);
            continue;
        }
        current = current->next;
    }
}

void add_to_free_list(block_t *block)
{
    block->next = g_heap.free_list;
    block->prev = NULL;
    if (g_heap.free_list)
        g_heap.free_list->prev = block;
    g_heap.free_list = block;
}

void remove_from_free_list(block_t *block)
{
    if (block->prev)
        block->prev->next = block->next;
    else
        g_heap.free_list = block->next;
    
    if (block->next)
        block->next->prev = block->prev;
    
    block->next = NULL;
    block->prev = NULL;
}
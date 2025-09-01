/*
** EPITECH PROJECT, 2025
** Malloc
** File description:
** Utility functions for malloc implementation
*/

#include "malloc.h"

void *heap_start = NULL;
block_t *free_list = NULL;

size_t align_size(size_t size)
{
    return (size + ALIGN - 1) & ~(ALIGN - 1);
}

block_t *find_best_fit(size_t size)
{
    block_t *current = free_list;
    block_t *best = NULL;
    
    while (current) {
        if (current->free && current->size >= size) {
            if (!best || current->size < best->size)
                best = current;
        }
        current = current->next;
    }
    return best;
}

void split_block(block_t *block, size_t size)
{
    if (block->size <= size + sizeof(block_t) + MIN_BLOCK_SIZE)
        return;
    
    block_t *new_block = (block_t *)((char *)block + sizeof(block_t) + size);
    new_block->size = block->size - size - sizeof(block_t);
    new_block->free = 1;
    new_block->next = block->next;
    new_block->prev = block;
    
    if (block->next)
        block->next->prev = new_block;
    
    block->next = new_block;
    block->size = size;
}

void merge_blocks(block_t *block)
{
    if (!block)
        return;
    
    if (block->next && block->next->free) {
        block->size += sizeof(block_t) + block->next->size;
        if (block->next->next)
            block->next->next->prev = block;
        block->next = block->next->next;
    }
    
    if (block->prev && block->prev->free) {
        block->prev->size += sizeof(block_t) + block->size;
        block->prev->next = block->next;
        if (block->next)
            block->next->prev = block->prev;
    }
}

void *expand_heap(size_t size)
{
    size_t total_size = sizeof(block_t) + size;
    size_t pages_needed = (total_size + PAGE_SIZE - 1) / PAGE_SIZE;
    size_t expand_size = pages_needed * PAGE_SIZE * 2;
    
    void *prev_brk = sbrk(0);
    if (sbrk(expand_size) == (void *)-1)
        return NULL;
    
    if (!heap_start)
        heap_start = prev_brk;
    
    block_t *new_block = (block_t *)prev_brk;
    new_block->size = expand_size - sizeof(block_t);
    new_block->free = 1;
    new_block->next = NULL;
    new_block->prev = NULL;
    
    if (free_list) {
        block_t *last = free_list;
        while (last->next)
            last = last->next;
        last->next = new_block;
        new_block->prev = last;
    } else {
        free_list = new_block;
    }
    
    return new_block;
}
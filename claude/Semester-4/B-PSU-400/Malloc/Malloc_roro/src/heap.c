/*
** EPITECH PROJECT, 2025
** Malloc
** File description:
** Heap management functions
*/

#include "my_malloc.h"
#include <string.h>

heap_t g_heap = {NULL, NULL, 0, NULL};

size_t align_size(size_t size)
{
    return (size + ALIGNMENT - 1) & ~(ALIGNMENT - 1);
}

static size_t get_aligned_heap_size(size_t size)
{
    size_t needed = size + sizeof(block_t);
    size_t pages = (needed + 2 * PAGE_SIZE - 1) / PAGE_SIZE;
    
    if (pages % 2 != 0)
        pages++;
    return pages * PAGE_SIZE;
}

void *extend_heap(size_t size)
{
    size_t heap_size = get_aligned_heap_size(size);
    void *new_break;
    block_t *new_block;

    if (g_heap.start == NULL) {
        g_heap.start = sbrk(heap_size);
        if (g_heap.start == (void *)-1)
            return NULL;
        g_heap.end = (char *)g_heap.start + heap_size;
        g_heap.total_size = heap_size;
    } else {
        new_break = sbrk(heap_size);
        if (new_break == (void *)-1)
            return NULL;
        g_heap.end = (char *)g_heap.end + heap_size;
        g_heap.total_size += heap_size;
    }

    new_block = (block_t *)((char *)g_heap.end - heap_size);
    new_block->size = heap_size - sizeof(block_t);
    new_block->is_free = 1;
    new_block->next = NULL;
    new_block->prev = NULL;

    add_to_free_list(new_block);
    return new_block;
}
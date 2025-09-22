/*
** EPITECH PROJECT, 2025
** Malloc
** File description:
** Debug and utility functions
*/

#include "malloc.h"
#include <stdio.h>

int is_valid_pointer(void *ptr)
{
    if (ptr == NULL)
        return 0;

    block_t *block = (block_t *)((char *)ptr - sizeof(block_t));

    // Check if pointer is within heap bounds
    if ((char *)block < (char *)heap_start || (char *)block >= (char *)heap_end)
        return 0;

    // Check if block is marked as used
    if (block->status != BLOCK_USED)
        return 0;

    return 1;
}

void print_heap_status(void)
{
    block_t *current = heap_start;
    int block_count = 0;
    size_t total_allocated = 0;
    size_t total_free = 0;

    printf("=== HEAP STATUS ===\n");
    printf("Heap start: %p\n", heap_start);
    printf("Heap end: %p\n", heap_end);

    while (current && (char *)current < (char *)heap_end) {
        printf("Block %d: addr=%p, size=%zu, status=%s\n",
               block_count,
               current,
               current->size,
               current->status == BLOCK_USED ? "USED" : "FREE");

        if (current->status == BLOCK_USED)
            total_allocated += current->size;
        else
            total_free += current->size;

        current = current->next;
        block_count++;

        // Safety check to avoid infinite loops
        if (block_count > 1000)
            break;
    }

    printf("Total blocks: %d\n", block_count);
    printf("Total allocated: %zu bytes\n", total_allocated);
    printf("Total free: %zu bytes\n", total_free);
    printf("==================\n");
}

size_t get_total_allocated(void)
{
    block_t *current = heap_start;
    size_t total = 0;

    while (current && (char *)current < (char *)heap_end) {
        if (current->status == BLOCK_USED)
            total += current->size;
        current = current->next;
    }

    return total;
}

size_t get_total_free(void)
{
    block_t *current = heap_start;
    size_t total = 0;

    while (current && (char *)current < (char *)heap_end) {
        if (current->status == BLOCK_FREE)
            total += current->size;
        current = current->next;
    }

    return total;
}
/*
** EPITECH PROJECT, 2025
** Malloc
** File description:
** Main malloc implementation
*/

#include "malloc.h"

// Global heap management variables
block_t *heap_start = NULL;
void *heap_end = NULL;

size_t align_size(size_t size)
{
    if (size == 0)
        return ALIGNMENT;

    return (size + ALIGNMENT - 1) & ~(ALIGNMENT - 1);
}

void init_heap(void)
{
    if (heap_start != NULL)
        return;

    // Initialize heap with sbrk
    heap_start = (block_t *)sbrk(0);
    heap_end = heap_start;

    if (heap_start == (void *)-1) {
        heap_start = NULL;
        return;
    }
}

void *request_memory(size_t size)
{
    size_t total_size = sizeof(block_t) + size;
    size_t pages_needed = (total_size + PAGE_SIZE - 1) / PAGE_SIZE;
    size_t request_size = pages_needed * PAGE_SIZE;

    void *prev_break = sbrk(request_size);
    if (prev_break == (void *)-1)
        return NULL;

    heap_end = (char *)heap_end + request_size;
    return prev_break;
}

block_t *find_best_fit(size_t size)
{
    block_t *current = heap_start;
    block_t *best_fit = NULL;

    while (current && (char *)current < (char *)heap_end) {
        if (current->status == BLOCK_FREE && current->size >= size) {
            if (best_fit == NULL || current->size < best_fit->size)
                best_fit = current;
        }
        current = current->next;
    }

    return best_fit;
}

block_t *split_block(block_t *block, size_t size)
{
    if (block->size <= size + sizeof(block_t) + MIN_BLOCK_SIZE)
        return block;

    // Create new block after the allocated space
    block_t *new_block = (block_t *)((char *)block + sizeof(block_t) + size);
    new_block->size = block->size - size - sizeof(block_t);
    new_block->status = BLOCK_FREE;
    new_block->next = block->next;
    new_block->prev = block;

    if (block->next)
        block->next->prev = new_block;

    block->next = new_block;
    block->size = size;

    return block;
}

void merge_free_blocks(void)
{
    block_t *current = heap_start;

    while (current && current->next) {
        if (current->status == BLOCK_FREE && current->next->status == BLOCK_FREE) {
            // Merge current with next
            current->size += sizeof(block_t) + current->next->size;

            if (current->next->next)
                current->next->next->prev = current;

            current->next = current->next->next;
        } else {
            current = current->next;
        }
    }
}

void *malloc(size_t size)
{
    if (size == 0)
        return NULL;

    init_heap();
    if (heap_start == NULL)
        return NULL;

    size_t aligned_size = align_size(size);
    block_t *block = find_best_fit(aligned_size);

    if (block == NULL) {
        // No suitable block found, request more memory
        void *new_memory = request_memory(aligned_size);
        if (new_memory == NULL)
            return NULL;

        block = (block_t *)new_memory;
        block->size = aligned_size;
        block->status = BLOCK_USED;
        block->next = NULL;
        block->prev = NULL;

        // Link to existing heap
        if (heap_start == new_memory) {
            // First allocation
            heap_start = block;
        } else {
            // Find last block and link
            block_t *last = heap_start;
            while (last->next)
                last = last->next;
            last->next = block;
            block->prev = last;
        }
    } else {
        // Use existing block
        block = split_block(block, aligned_size);
        block->status = BLOCK_USED;
    }

    return (char *)block + sizeof(block_t);
}

void free(void *ptr)
{
    if (ptr == NULL)
        return;

    block_t *block = (block_t *)((char *)ptr - sizeof(block_t));

    // Basic validation
    if (block->status != BLOCK_USED)
        return;

    block->status = BLOCK_FREE;
    merge_free_blocks();
}

void *calloc(size_t nmemb, size_t size)
{
    if (nmemb == 0 || size == 0)
        return NULL;

    // Check for overflow
    if (nmemb > SIZE_MAX / size) {
        errno = ENOMEM;
        return NULL;
    }

    size_t total_size = nmemb * size;
    void *ptr = malloc(total_size);

    if (ptr != NULL)
        memset(ptr, 0, total_size);

    return ptr;
}

void *realloc(void *ptr, size_t size)
{
    if (ptr == NULL)
        return malloc(size);

    if (size == 0) {
        free(ptr);
        return NULL;
    }

    block_t *block = (block_t *)((char *)ptr - sizeof(block_t));
    if (block->status != BLOCK_USED)
        return NULL;

    size_t aligned_size = align_size(size);

    // If new size fits in current block
    if (aligned_size <= block->size)
        return ptr;

    // Allocate new block and copy data
    void *new_ptr = malloc(size);
    if (new_ptr == NULL)
        return NULL;

    size_t copy_size = block->size < size ? block->size : size;
    memcpy(new_ptr, ptr, copy_size);
    free(ptr);

    return new_ptr;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    if (nmemb == 0 || size == 0)
        return realloc(ptr, 0);

    // Check for overflow
    if (nmemb > SIZE_MAX / size) {
        errno = ENOMEM;
        return NULL;
    }

    return realloc(ptr, nmemb * size);
}
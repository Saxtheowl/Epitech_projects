/*
** EPITECH PROJECT, 2025
** Malloc
** File description:
**   Public interface for allocator
*/

#ifndef MMALLOC_H
#define MMALLOC_H

#include <stddef.h>

void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);

typedef struct block_s {
    size_t size;
    int free;
    struct block_s *next;
    struct block_s *prev;
} block_t;

typedef struct arena_s {
    block_t *head;
    size_t page_sz;
} arena_t;

arena_t *get_arena(void);
size_t align_pow2(size_t n);
void *sys_sbrk_aligned(size_t inc);
block_t *find_best_fit(size_t size);
block_t *split_block(block_t *b, size_t size);
block_t *extend_heap(size_t size);
void coalesce(block_t *b);
void mark_free(block_t *b);

#define HEADER_SIZE ((sizeof(block_t) + (sizeof(void*) - 1)) & ~((sizeof(void*) - 1)))

#endif /* MMALLOC_H */


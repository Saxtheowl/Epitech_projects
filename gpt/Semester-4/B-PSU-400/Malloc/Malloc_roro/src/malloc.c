/*
** EPITECH PROJECT, 2025
** Malloc
** File description:
**   malloc implementation (best-fit, aligned, sbrk)
*/

#include <unistd.h>
#include <string.h>
#include "mmalloc.h"

static size_t round_align(size_t n)
{
    size_t a = align_pow2(sizeof(void*) * 2);
    size_t m = a - 1;

    return (n + m) & ~m;
}

void *malloc(size_t size)
{
    size_t need = 0;
    block_t *b = NULL;
    arena_t *ar = NULL;

    if (size == 0)
        size = 1;
    need = round_align(size);
    b = find_best_fit(need);
    if (!b) {
        b = extend_heap(need);
        if (!b)
            return NULL;
    } else {
        b = split_block(b, need);
        b->free = 0;
    }
    return (char *)b + HEADER_SIZE;
}


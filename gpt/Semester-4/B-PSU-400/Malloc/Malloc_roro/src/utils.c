/*
** EPITECH PROJECT, 2025
** Malloc
** File description:
**   Free list utilities
*/

#include <string.h>
#include "mmalloc.h"

block_t *find_best_fit(size_t size)
{
    arena_t *a = get_arena();
    block_t *best = NULL;
    block_t *it = a->head;

    while (it) {
        if (it->free && it->size >= size) {
            if (!best || it->size < best->size)
                best = it;
            if (it->size == size)
                break;
        }
        it = it->next;
    }
    return best;
}

block_t *split_block(block_t *b, size_t size)
{
    char *raw = (char *)b;
    size_t remaining = 0;
    block_t *nb = NULL;

    if (!b || b->size <= size + HEADER_SIZE)
        return b;
    remaining = b->size - size - HEADER_SIZE;
    nb = (block_t *)(raw + HEADER_SIZE + size);
    nb->size = remaining;
    nb->free = 1;
    nb->next = b->next;
    nb->prev = b;
    if (b->next)
        b->next->prev = nb;
    b->next = nb;
    b->size = size;
    return b;
}

void coalesce(block_t *b)
{
    if (!b)
        return;
    if (b->next && b->next->free) {
        block_t *n = b->next;
        b->size += HEADER_SIZE + n->size;
        b->next = n->next;
        if (n->next)
            n->next->prev = b;
    }
    if (b->prev && b->prev->free) {
        block_t *p = b->prev;
        p->size += HEADER_SIZE + b->size;
        p->next = b->next;
        if (b->next)
            b->next->prev = p;
    }
}

void mark_free(block_t *b)
{
    b->free = 1;
    coalesce(b);
}


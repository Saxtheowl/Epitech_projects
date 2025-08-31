/*
** EPITECH PROJECT, 2025
** Malloc
** File description:
**   Arena and system allocation helpers
*/

#define _GNU_SOURCE
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <errno.h>
#include "mmalloc.h"

static arena_t g_arena = {0};

arena_t *get_arena(void)
{
    if (g_arena.page_sz == 0) {
        long ps = sysconf(_SC_PAGESIZE);
        if (ps <= 0)
            ps = 4096;
        g_arena.page_sz = (size_t)ps;
        g_arena.head = NULL;
    }
    return &g_arena;
}

size_t align_pow2(size_t n)
{
    size_t a = sizeof(void*) * 2;

    if (n == 0)
        return a;
    a = 1;
    while (a < n)
        a <<= 1;
    return a;
}

static void *raw_sbrk(ptrdiff_t inc)
{
    void *p = sbrk(inc);
    if (p == (void *)-1)
        return NULL;
    return p;
}

void *sys_sbrk_aligned(size_t inc)
{
    arena_t *a = get_arena();
    void *cur = raw_sbrk(0);
    size_t two_pages = a->page_sz * 2;
    size_t need = inc;
    unsigned long cur_ul = (unsigned long)cur;
    unsigned long next_boundary = (cur_ul + two_pages - 1) / two_pages * two_pages;
    unsigned long target = next_boundary;

    if (next_boundary - cur_ul >= inc) {
        need = (size_t)(next_boundary - cur_ul);
    } else {
        unsigned long rem = inc - (next_boundary - cur_ul);
        unsigned long k = (rem + two_pages - 1) / two_pages;
        target = next_boundary + k * two_pages;
        need = (size_t)(target - cur_ul);
    }
    if (need == 0)
        return cur;
    return raw_sbrk((ptrdiff_t)need);
}

block_t *extend_heap(size_t size)
{
    arena_t *a = get_arena();
    size_t total = HEADER_SIZE + size;
    void *base = sys_sbrk_aligned(total);
    block_t *b = NULL;

    if (!base)
        return NULL;
    b = (block_t *)base;
    b->size = size;
    b->free = 0;
    b->next = NULL;
    b->prev = NULL;
    if (!a->head) {
        a->head = b;
    } else {
        block_t *it = a->head;
        while (it->next)
            it = it->next;
        it->next = b;
        b->prev = it;
    }
    return b;
}


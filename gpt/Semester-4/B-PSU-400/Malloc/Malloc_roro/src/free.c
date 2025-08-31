/*
** EPITECH PROJECT, 2025
** Malloc
** File description:
**   free implementation
*/

#include <unistd.h>
#include "mmalloc.h"

void free(void *ptr)
{
    block_t *b = NULL;

    if (!ptr)
        return;
    b = (block_t *)((char *)ptr - HEADER_SIZE);
    mark_free(b);
}


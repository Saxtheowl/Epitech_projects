/*
** EPITECH PROJECT, 2025
** Malloc
** File description:
**   calloc implementation
*/

#include <string.h>
#include "mmalloc.h"

void *calloc(size_t nmemb, size_t size)
{
    size_t total = 0;
    void *p = NULL;

    if (nmemb != 0 && size > (size_t)-1 / nmemb)
        return NULL;
    total = nmemb * size;
    p = malloc(total);
    if (!p)
        return NULL;
    memset(p, 0, total);
    return p;
}


/*
** EPITECH PROJECT, 2025
** Malloc
** File description:
** reallocarray implementation
*/

#include "malloc.h"

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    if (nmemb == 0 || size == 0) {
        free(ptr);
        return NULL;
    }
    
    if (nmemb > SIZE_MAX / size)
        return NULL;
    
    return realloc(ptr, nmemb * size);
}
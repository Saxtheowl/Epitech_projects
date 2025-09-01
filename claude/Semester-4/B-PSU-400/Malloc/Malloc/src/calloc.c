/*
** EPITECH PROJECT, 2025
** Malloc
** File description:
** calloc implementation
*/

#include "malloc.h"

static void *my_memset(void *s, int c, size_t n)
{
    unsigned char *ptr = (unsigned char *)s;
    
    while (n--)
        *ptr++ = (unsigned char)c;
    return s;
}

void *calloc(size_t nmemb, size_t size)
{
    if (nmemb == 0 || size == 0)
        return NULL;
    
    if (nmemb > SIZE_MAX / size)
        return NULL;
    
    size_t total_size = nmemb * size;
    void *ptr = malloc(total_size);
    
    if (ptr)
        my_memset(ptr, 0, total_size);
    
    return ptr;
}
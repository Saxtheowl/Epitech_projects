/*
** EPITECH PROJECT, 2025
** Malloc
** File description:
** Header file for malloc implementation
*/

#ifndef MALLOC_H_
#define MALLOC_H_

#include <unistd.h>
#include <stddef.h>
#include <sys/mman.h>
#include <stdint.h>

#ifndef SIZE_MAX
#define SIZE_MAX ((size_t)-1)
#endif

#define ALIGN 8
#define PAGE_SIZE 4096
#define MIN_BLOCK_SIZE 16

typedef struct block_s {
    size_t size;
    int free;
    struct block_s *next;
    struct block_s *prev;
} block_t;

extern void *heap_start;
extern block_t *free_list;

void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);

size_t align_size(size_t size);
block_t *find_best_fit(size_t size);
block_t *create_block(size_t size);
void split_block(block_t *block, size_t size);
void merge_blocks(block_t *block);
void *expand_heap(size_t size);

#endif /* !MALLOC_H_ */
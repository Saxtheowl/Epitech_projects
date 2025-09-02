/*
** EPITECH PROJECT, 2025
** Malloc
** File description:
** Custom malloc implementation header
*/

#ifndef MY_MALLOC_H_
#define MY_MALLOC_H_

#define _GNU_SOURCE
#include <stddef.h>
#include <unistd.h>
#include <sys/mman.h>

#define ALIGNMENT 16
#define PAGE_SIZE 4096
#define MIN_BLOCK_SIZE 32

typedef struct block_s {
    size_t size;
    int is_free;
    struct block_s *next;
    struct block_s *prev;
} block_t;

typedef struct heap_s {
    void *start;
    void *end;
    size_t total_size;
    block_t *free_list;
} heap_t;

extern heap_t g_heap;

void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);

size_t align_size(size_t size);
void *extend_heap(size_t size);
block_t *find_best_fit(size_t size);
block_t *split_block(block_t *block, size_t size);
void merge_free_blocks(block_t *block);
void add_to_free_list(block_t *block);
void remove_from_free_list(block_t *block);
void *get_user_ptr(block_t *block);
block_t *get_block_from_ptr(void *ptr);
int is_valid_ptr(void *ptr);

#endif /* !MY_MALLOC_H_ */
/*
** EPITECH PROJECT, 2025
** Malloc
** File description:
** Custom malloc implementation header
*/

#pragma once

#define _GNU_SOURCE
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

#define ALIGNMENT 16
#define PAGE_SIZE 4096
#define MIN_BLOCK_SIZE 32

// Block states
#define BLOCK_FREE 0
#define BLOCK_USED 1

// Block structure for linked list
typedef struct block_s {
    size_t size;           // Size of the data area
    int status;            // BLOCK_FREE or BLOCK_USED
    struct block_s *next;  // Next block in the list
    struct block_s *prev;  // Previous block in the list
} block_t;

// Global variables
extern block_t *heap_start;
extern void *heap_end;

// Internal functions
void *request_memory(size_t size);
block_t *find_best_fit(size_t size);
block_t *split_block(block_t *block, size_t size);
void merge_free_blocks(void);
size_t align_size(size_t size);
int is_valid_pointer(void *ptr);
void init_heap(void);

// API functions
void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);

// Debug functions
void print_heap_status(void);
size_t get_total_allocated(void);
size_t get_total_free(void);
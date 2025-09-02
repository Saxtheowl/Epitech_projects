/*
** EPITECH PROJECT, 2025
** Malloc
** File description:
** malloc function implementation
*/

#include "my_malloc.h"

void *malloc(size_t size)
{
    block_t *block;
    size_t aligned_size;

    if (size == 0)
        return NULL;

    aligned_size = align_size(size);
    block = find_best_fit(aligned_size);

    if (!block) {
        block = extend_heap(aligned_size);
        if (!block)
            return NULL;
    }

    remove_from_free_list(block);
    block = split_block(block, aligned_size);
    block->is_free = 0;

    return get_user_ptr(block);
}
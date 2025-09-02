/*
** EPITECH PROJECT, 2025
** Malloc
** File description:
** free function implementation
*/

#include "my_malloc.h"

void free(void *ptr)
{
    block_t *block;

    if (!is_valid_ptr(ptr))
        return;

    block = get_block_from_ptr(ptr);
    block->is_free = 1;
    add_to_free_list(block);
    merge_free_blocks(block);
}
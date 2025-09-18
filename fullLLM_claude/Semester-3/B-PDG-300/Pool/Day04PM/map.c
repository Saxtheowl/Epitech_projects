/*
** EPITECH PROJECT, 2024
** Paradigms Seminar
** File description:
** Exercise 04 - Map implementation
*/

#include "map.h"
#include <stdlib.h>

unsigned int map_get_size(map_t map)
{
    return list_get_size(map);
}

bool map_is_empty(map_t map)
{
    return list_is_empty(map);
}

static pair_t *create_pair(void *key, void *value)
{
    pair_t *pair = malloc(sizeof(pair_t));
    if (!pair)
        return NULL;
    pair->key = key;
    pair->value = value;
    return pair;
}

static pair_t *find_pair_by_key(map_t map, void *key, key_comparator_t key_cmp)
{
    node_t *current = map;
    
    while (current) {
        pair_t *pair = (pair_t *)current->value;
        if (pair && key_cmp(pair->key, key) == 0)
            return pair;
        current = current->next;
    }
    return NULL;
}

bool map_add_elem(map_t *map_ptr, void *key, void *value, key_comparator_t key_cmp)
{
    if (!map_ptr || !key_cmp)
        return false;
        
    // Check if key already exists and update value
    pair_t *existing_pair = find_pair_by_key(*map_ptr, key, key_cmp);
    if (existing_pair) {
        existing_pair->value = value;
        return true;
    }
    
    // Create new pair and add to list
    pair_t *new_pair = create_pair(key, value);
    if (!new_pair)
        return false;
        
    return list_add_elem_at_front(map_ptr, new_pair);
}

bool map_del_elem(map_t *map_ptr, void *key, key_comparator_t key_cmp)
{
    if (!map_ptr || !key_cmp)
        return false;
        
    node_t *current = *map_ptr;
    unsigned int position = 0;
    
    while (current) {
        pair_t *pair = (pair_t *)current->value;
        if (pair && key_cmp(pair->key, key) == 0) {
            free(pair);
            return list_del_elem_at_position(map_ptr, position);
        }
        current = current->next;
        position++;
    }
    return false;
}

void map_clear(map_t *map_ptr)
{
    if (!map_ptr)
        return;
        
    node_t *current = *map_ptr;
    while (current) {
        pair_t *pair = (pair_t *)current->value;
        if (pair)
            free(pair);
        current = current->next;
    }
    list_clear(map_ptr);
}

void *map_get_elem(map_t map, void *key, key_comparator_t key_cmp)
{
    if (!key_cmp)
        return NULL;
        
    pair_t *pair = find_pair_by_key(map, key, key_cmp);
    return pair ? pair->value : NULL;
}
#include <stdlib.h>
#include "../map.h"

unsigned int map_get_size(map_t map)
{
    return list_get_size(map);
}

bool map_is_empty(map_t map)
{
    return list_is_empty(map);
}

static pair_t *find_pair_by_key(map_t map, void *key, key_comparator_t key_cmp)
{
    node_t *current = map;
    pair_t *pair;

    if (key_cmp == NULL)
        return NULL;

    while (current != NULL) {
        pair = (pair_t *)current->value;
        if (pair != NULL && key_cmp(pair->key, key) == 0)
            return pair;
        current = current->next;
    }
    return NULL;
}

bool map_add_elem(map_t *map_ptr, void *key, void *value, key_comparator_t key_cmp)
{
    pair_t *new_pair;
    pair_t *existing_pair;

    if (map_ptr == NULL || key_cmp == NULL)
        return false;

    existing_pair = find_pair_by_key(*map_ptr, key, key_cmp);
    if (existing_pair != NULL) {
        existing_pair->value = value;
        return true;
    }

    new_pair = malloc(sizeof(pair_t));
    if (new_pair == NULL)
        return false;

    new_pair->key = key;
    new_pair->value = value;

    if (!list_add_elem_at_front(map_ptr, new_pair)) {
        free(new_pair);
        return false;
    }

    return true;
}

bool map_del_elem(map_t *map_ptr, void *key, key_comparator_t key_cmp)
{
    node_t *current;
    node_t *previous = NULL;
    pair_t *pair;

    if (map_ptr == NULL || *map_ptr == NULL || key_cmp == NULL)
        return false;

    current = *map_ptr;
    while (current != NULL) {
        pair = (pair_t *)current->value;
        if (pair != NULL && key_cmp(pair->key, key) == 0) {
            if (previous == NULL) {
                *map_ptr = current->next;
            } else {
                previous->next = current->next;
            }
            free(pair);
            free(current);
            return true;
        }
        previous = current;
        current = current->next;
    }
    return false;
}

void map_clear(map_t *map_ptr)
{
    node_t *current;
    node_t *next;

    if (map_ptr == NULL || *map_ptr == NULL)
        return;

    current = *map_ptr;
    while (current != NULL) {
        next = current->next;
        if (current->value != NULL)
            free(current->value);
        free(current);
        current = next;
    }
    *map_ptr = NULL;
}

void *map_get_elem(map_t map, void *key, key_comparator_t key_cmp)
{
    pair_t *pair = find_pair_by_key(map, key, key_cmp);
    
    if (pair == NULL)
        return NULL;
    return pair->value;
}
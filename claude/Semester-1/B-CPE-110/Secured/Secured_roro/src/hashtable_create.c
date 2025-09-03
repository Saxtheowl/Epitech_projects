/*
** EPITECH PROJECT, 2025
** Secured
** File description:
** Hashtable creation and destruction
*/

#include "hashtable.h"
#include <stdlib.h>

hashtable_t *new_hashtable(int (*hash_func)(char *, int), int len)
{
    hashtable_t *ht = NULL;
    int i = 0;
    
    if (!hash_func || len <= 0)
        return NULL;
    
    ht = malloc(sizeof(hashtable_t));
    if (!ht)
        return NULL;
    
    ht->buckets = malloc(sizeof(hash_node_t *) * len);
    if (!ht->buckets) {
        free(ht);
        return NULL;
    }
    
    for (i = 0; i < len; i++)
        ht->buckets[i] = NULL;
    
    ht->hash_func = hash_func;
    ht->size = len;
    
    return ht;
}

static void free_node_list(hash_node_t *node)
{
    hash_node_t *next = NULL;
    
    while (node) {
        next = node->next;
        free(node->key);
        free(node->value);
        free(node);
        node = next;
    }
}

void delete_hashtable(hashtable_t *ht)
{
    int i = 0;
    
    if (!ht)
        return;
    
    if (ht->buckets) {
        for (i = 0; i < ht->size; i++) {
            if (ht->buckets[i])
                free_node_list(ht->buckets[i]);
        }
        free(ht->buckets);
    }
    
    free(ht);
}
/*
** EPITECH PROJECT, 2025
** Secured
** File description:
** Hashtable operations (insert, delete, search)
*/

#include "hashtable.h"
#include <stdlib.h>
#include <string.h>

static hash_node_t *create_node(char *key, char *value, int hash_value)
{
    hash_node_t *node = malloc(sizeof(hash_node_t));
    
    if (!node)
        return NULL;
    
    node->key = malloc(strlen(key) + 1);
    node->value = malloc(strlen(value) + 1);
    
    if (!node->key || !node->value) {
        free(node->key);
        free(node->value);
        free(node);
        return NULL;
    }
    
    strcpy(node->key, key);
    strcpy(node->value, value);
    node->hash_value = hash_value;
    node->next = NULL;
    
    return node;
}

static hash_node_t *find_node(hash_node_t *head, char *key)
{
    hash_node_t *current = head;
    
    while (current) {
        if (strcmp(current->key, key) == 0)
            return current;
        current = current->next;
    }
    
    return NULL;
}

int ht_insert(hashtable_t *ht, char *key, char *value)
{
    int hash_value = 0;
    int index = 0;
    hash_node_t *existing = NULL;
    hash_node_t *new_node = NULL;
    
    if (!ht || !key || !value)
        return -1;
    
    hash_value = ht->hash_func(key, ht->size);
    index = hash_value % ht->size;
    
    existing = find_node(ht->buckets[index], key);
    if (existing) {
        free(existing->value);
        existing->value = malloc(strlen(value) + 1);
        if (!existing->value)
            return -1;
        strcpy(existing->value, value);
        return 0;
    }
    
    new_node = create_node(key, value, hash_value);
    if (!new_node)
        return -1;
    
    new_node->next = ht->buckets[index];
    ht->buckets[index] = new_node;
    
    return 0;
}

int ht_delete(hashtable_t *ht, char *key)
{
    int hash_value = 0;
    int index = 0;
    hash_node_t *current = NULL;
    hash_node_t *prev = NULL;
    
    if (!ht || !key)
        return -1;
    
    hash_value = ht->hash_func(key, ht->size);
    index = hash_value % ht->size;
    
    current = ht->buckets[index];
    
    while (current) {
        if (strcmp(current->key, key) == 0) {
            if (prev)
                prev->next = current->next;
            else
                ht->buckets[index] = current->next;
            
            free(current->key);
            free(current->value);
            free(current);
            return 0;
        }
        prev = current;
        current = current->next;
    }
    
    return -1;
}

char *ht_search(hashtable_t *ht, char *key)
{
    int hash_value = 0;
    int index = 0;
    hash_node_t *node = NULL;
    
    if (!ht || !key)
        return NULL;
    
    hash_value = ht->hash_func(key, ht->size);
    index = hash_value % ht->size;
    
    node = find_node(ht->buckets[index], key);
    if (node)
        return node->value;
    
    return NULL;
}
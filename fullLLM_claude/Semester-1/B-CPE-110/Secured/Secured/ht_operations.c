#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hashtable.h"

static char *my_strdup(const char *s)
{
    char *dup;
    int len = 0;
    int i;

    while (s[len])
        len++;
    
    dup = malloc(len + 1);
    if (!dup)
        return NULL;
    
    for (i = 0; i <= len; i++)
        dup[i] = s[i];
    
    return dup;
}

int ht_insert(hashtable_t *ht, char *key, char *value)
{
    int index;
    hash_node_t *node, *current;

    if (!ht || !key || !value)
        return -1;
    
    index = ht->hash_func(key, ht->size);
    current = ht->buckets[index];
    
    while (current) {
        if (strcmp(current->key, key) == 0) {
            free(current->value);
            current->value = my_strdup(value);
            return current->value ? 0 : -1;
        }
        current = current->next;
    }
    
    node = malloc(sizeof(hash_node_t));
    if (!node)
        return -1;
    
    node->key = my_strdup(key);
    node->value = my_strdup(value);
    
    if (!node->key || !node->value) {
        free(node->key);
        free(node->value);
        free(node);
        return -1;
    }
    
    node->hash_value = ht->hash_func(key, ht->size);
    node->next = ht->buckets[index];
    ht->buckets[index] = node;
    
    return 0;
}

int ht_delete(hashtable_t *ht, char *key)
{
    int index;
    hash_node_t *current, *prev = NULL;

    if (!ht || !key)
        return -1;
    
    index = ht->hash_func(key, ht->size);
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
    int index;
    hash_node_t *current;

    if (!ht || !key)
        return NULL;
    
    index = ht->hash_func(key, ht->size);
    current = ht->buckets[index];
    
    while (current) {
        if (strcmp(current->key, key) == 0)
            return current->value;
        current = current->next;
    }
    
    return NULL;
}

void ht_dump(hashtable_t *ht)
{
    hash_node_t *current;
    int i;

    if (!ht)
        return;
    
    for (i = 0; i < ht->size; i++) {
        printf("[%d]:\n", i);
        current = ht->buckets[i];
        while (current) {
            printf("> %d - %s\n", current->hash_value, current->value);
            current = current->next;
        }
    }
}
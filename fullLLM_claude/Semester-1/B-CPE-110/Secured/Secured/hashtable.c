#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hashtable.h"

hashtable_t *new_hashtable(int (*hash)(char *, int), int len)
{
    hashtable_t *ht = malloc(sizeof(hashtable_t));
    int i;

    if (!ht)
        return NULL;
    
    ht->buckets = malloc(sizeof(hash_node_t*) * len);
    if (!ht->buckets) {
        free(ht);
        return NULL;
    }
    
    for (i = 0; i < len; i++)
        ht->buckets[i] = NULL;
    
    ht->size = len;
    ht->hash_func = hash;
    return ht;
}

void delete_hashtable(hashtable_t *ht)
{
    hash_node_t *current, *temp;
    int i;

    if (!ht)
        return;
    
    for (i = 0; i < ht->size; i++) {
        current = ht->buckets[i];
        while (current) {
            temp = current;
            current = current->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
    
    free(ht->buckets);
    free(ht);
}
/*
** EPITECH PROJECT, 2025
** Secured
** File description:
** Hashtable dump function for debugging
*/

#include "hashtable.h"
#include <unistd.h>

static void write_str(const char *str)
{
    int i = 0;
    
    while (str[i]) {
        write(1, &str[i], 1);
        i++;
    }
}

static void write_number(int num)
{
    char buffer[32];
    int i = 0;
    
    if (num == 0) {
        write(1, "0", 1);
        return;
    }
    
    if (num < 0) {
        write(1, "-", 1);
        num = -num;
    }
    
    while (num > 0) {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }
    
    while (i > 0) {
        write(1, &buffer[--i], 1);
    }
}

void ht_dump(hashtable_t *ht)
{
    int i = 0;
    hash_node_t *current = NULL;
    
    if (!ht)
        return;
    
    for (i = 0; i < ht->size; i++) {
        write_str("[");
        write_number(i);
        write_str("]:");
        
        current = ht->buckets[i];
        while (current) {
            write_str("\n> ");
            write_number(current->hash_value);
            write_str(" - ");
            write_str(current->value);
            current = current->next;
        }
        
        write_str("\n");
    }
}
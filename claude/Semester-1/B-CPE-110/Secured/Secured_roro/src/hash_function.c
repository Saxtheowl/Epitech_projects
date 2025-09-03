/*
** EPITECH PROJECT, 2025
** Secured
** File description:
** Hash function implementation
*/

#include "hashtable.h"

int hash(char *key, int len)
{
    int hash_value = 5381;
    int i = 0;
    
    (void)len;
    if (!key)
        return 0;
    
    while (key[i]) {
        hash_value = ((hash_value << 5) + hash_value) + key[i];
        i++;
    }
    
    if (hash_value < 0)
        hash_value = -hash_value;
    
    return hash_value;
}
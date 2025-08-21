/*
** EPITECH PROJECT, 2024
** Antman
** File description:
** Utility functions
*/

#include "compression.h"

int my_strlen(char *str)
{
    int len = 0;
    
    if (!str)
        return 0;
    
    while (str[len])
        len++;
    
    return len;
}

int my_strcmp(char *s1, char *s2)
{
    int i = 0;
    
    if (!s1 || !s2)
        return -1;
    
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    
    return s1[i] - s2[i];
}

char *my_strdup(char *str)
{
    char *dup;
    int len;
    int i;
    
    if (!str)
        return NULL;
    
    len = my_strlen(str);
    dup = malloc(len + 1);
    
    if (!dup)
        return NULL;
    
    for (i = 0; i < len; i++)
        dup[i] = str[i];
    
    dup[len] = '\0';
    return dup;
}

void my_putstr(char *str)
{
    if (!str)
        return;
    
    write(2, str, my_strlen(str));
}

dictionary_t *create_dictionary(void)
{
    dictionary_t *dict = malloc(sizeof(dictionary_t));
    
    if (!dict)
        return NULL;
    
    dict->count = 0;
    
    for (int i = 0; i < MAX_DICT_SIZE; i++) {
        dict->entries[i].word = NULL;
        dict->entries[i].index = -1;
    }
    
    return dict;
}

void free_dictionary(dictionary_t *dict)
{
    if (!dict)
        return;
    
    for (int i = 0; i < dict->count; i++) {
        if (dict->entries[i].word)
            free(dict->entries[i].word);
    }
    
    free(dict);
}

int find_in_dictionary(dictionary_t *dict, char *word)
{
    if (!dict || !word)
        return -1;
    
    for (int i = 0; i < dict->count; i++) {
        if (dict->entries[i].word && my_strcmp(dict->entries[i].word, word) == 0)
            return dict->entries[i].index;
    }
    
    return -1;
}

void add_to_dictionary(dictionary_t *dict, char *word)
{
    if (!dict || !word || dict->count >= MAX_DICT_SIZE)
        return;
    
    dict->entries[dict->count].word = my_strdup(word);
    dict->entries[dict->count].index = dict->count;
    dict->count++;
}
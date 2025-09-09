#include "common.h"

static unsigned int hash_string(const char *str, int length)
{
    unsigned int hash = 5381;
    int i;
    
    for (i = 0; i < length; i++)
        hash = ((hash << 5) + hash) + (unsigned char)str[i];
    
    return hash % MAX_DICT_SIZE;
}

static int string_compare(const char *s1, const char *s2, int length)
{
    int i;
    
    for (i = 0; i < length; i++) {
        if (s1[i] != s2[i])
            return 0;
    }
    return 1;
}

dictionary_t *dict_create(void)
{
    dictionary_t *dict = malloc(sizeof(dictionary_t));
    int i;
    
    if (!dict)
        return NULL;
    
    for (i = 0; i < MAX_DICT_SIZE; i++)
        dict->entries[i] = NULL;
    
    dict->next_index = 1;
    return dict;
}

void dict_free(dictionary_t *dict)
{
    int i;
    dict_entry_t *entry, *next;
    
    if (!dict)
        return;
    
    for (i = 0; i < MAX_DICT_SIZE; i++) {
        entry = dict->entries[i];
        while (entry) {
            next = entry->next;
            if (entry->pattern)
                free(entry->pattern);
            free(entry);
            entry = next;
        }
    }
    
    free(dict);
}

int dict_add_pattern(dictionary_t *dict, const char *pattern, int length)
{
    unsigned int hash;
    dict_entry_t *entry;
    int i;
    
    if (!dict || !pattern || length <= 0)
        return -1;
    
    hash = hash_string(pattern, length);
    entry = dict->entries[hash];
    
    while (entry) {
        if (string_compare(entry->pattern, pattern, length)) {
            entry->count++;
            return entry->index;
        }
        entry = entry->next;
    }
    
    entry = malloc(sizeof(dict_entry_t));
    if (!entry)
        return -1;
    
    entry->pattern = malloc(length);
    if (!entry->pattern) {
        free(entry);
        return -1;
    }
    
    for (i = 0; i < length; i++)
        entry->pattern[i] = pattern[i];
    
    entry->index = dict->next_index++;
    entry->count = 1;
    entry->next = dict->entries[hash];
    dict->entries[hash] = entry;
    
    return entry->index;
}

dict_entry_t *dict_find_pattern(dictionary_t *dict, const char *pattern, int length)
{
    unsigned int hash;
    dict_entry_t *entry;
    
    if (!dict || !pattern || length <= 0)
        return NULL;
    
    hash = hash_string(pattern, length);
    entry = dict->entries[hash];
    
    while (entry) {
        if (string_compare(entry->pattern, pattern, length))
            return entry;
        entry = entry->next;
    }
    
    return NULL;
}
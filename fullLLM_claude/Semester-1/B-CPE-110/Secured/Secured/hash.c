#include "hashtable.h"

int hash(char *key, int len)
{
    unsigned int hash_value = 5381;
    int i = 0;

    while (key[i]) {
        hash_value = ((hash_value << 5) + hash_value) + key[i];
        i++;
    }
    
    return hash_value % len;
}
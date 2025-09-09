#include "my.h"

char *my_strcat(char *dest, char const *src)
{
    int dest_len;
    int i = 0;
    
    if (dest == 0 || src == 0)
        return dest;
    
    dest_len = my_strlen(dest);
    
    while (src[i] != '\0') {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
    
    return dest;
}
#include "my_sokoban.h"

int my_strlen(char *str)
{
    int len = 0;
    
    if (!str)
        return 0;
    while (str[len])
        len++;
    return len;
}

char *my_strdup(char *str)
{
    char *dup;
    int i = 0;
    int len;
    
    if (!str)
        return NULL;
    len = my_strlen(str);
    dup = malloc(len + 1);
    if (!dup)
        return NULL;
    while (i < len) {
        dup[i] = str[i];
        i++;
    }
    dup[i] = '\0';
    return dup;
}

void my_putstr(char *str)
{
    if (!str)
        return;
    while (*str) {
        write(1, str, 1);
        str++;
    }
}
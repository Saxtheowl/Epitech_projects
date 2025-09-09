#include "sokoban.h"

int my_strlen(char const *str)
{
    int len = 0;
    
    if (!str)
        return 0;
    
    while (str[len])
        len++;
    
    return len;
}

char *my_strdup(char const *str)
{
    char *dup;
    int i = 0;
    
    if (!str)
        return NULL;
    
    dup = malloc(sizeof(char) * (my_strlen(str) + 1));
    if (!dup)
        return NULL;
    
    while (str[i]) {
        dup[i] = str[i];
        i++;
    }
    dup[i] = '\0';
    
    return dup;
}

void my_putstr(char const *str)
{
    if (!str)
        return;
    
    write(STDOUT_FILENO, str, my_strlen(str));
}
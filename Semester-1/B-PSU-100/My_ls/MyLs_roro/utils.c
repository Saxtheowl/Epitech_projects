#include "my_ls.h"

int my_putchar(char c)
{
    return write(1, &c, 1);
}

int my_putstr(char *str)
{
    int i = 0;
    
    if (!str)
        return 0;
    while (str[i]) {
        my_putchar(str[i]);
        i++;
    }
    return i;
}

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

int my_strcmp(char *s1, char *s2)
{
    int i = 0;
    
    if (!s1 || !s2)
        return (s1 == s2) ? 0 : (s1 ? 1 : -1);
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return s1[i] - s2[i];
}
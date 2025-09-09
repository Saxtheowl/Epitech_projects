#include "infin_add.h"

char *my_strdup(char const *str)
{
    int len = my_strlen(str);
    char *dup = malloc(len + 1);
    int i;
    
    if (!dup || !str)
        return 0;
    
    for (i = 0; i < len; i++)
        dup[i] = str[i];
    dup[i] = '\0';
    
    return dup;
}

int my_strlen(char const *str)
{
    int len = 0;
    
    if (!str)
        return 0;
    
    while (str[len])
        len++;
    
    return len;
}

void my_putstr(char const *str)
{
    if (!str)
        return;
    
    write(1, str, my_strlen(str));
}

char *remove_leading_zeros(char *str)
{
    int i = 0;
    int start = 0;
    
    if (!str || str[0] == '\0')
        return str;
    
    if (str[0] == '-')
        start = 1;
    
    while (str[start + i] == '0' && str[start + i + 1] != '\0')
        i++;
    
    if (i > 0) {
        int j = start;
        while (str[start + i]) {
            str[j] = str[start + i];
            j++;
            i++;
        }
        str[j] = '\0';
    }
    
    return str;
}
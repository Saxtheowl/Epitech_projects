#include "my.h"

char *my_revstr(char *str)
{
    int len;
    int i = 0;
    char temp;
    
    if (str == 0)
        return 0;
    
    len = my_strlen(str);
    
    while (i < len / 2) {
        temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
        i++;
    }
    
    return str;
}
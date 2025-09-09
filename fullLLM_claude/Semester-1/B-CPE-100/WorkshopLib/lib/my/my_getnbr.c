#include "my.h"

int my_getnbr(char const *str)
{
    int i = 0;
    int sign = 1;
    int result = 0;
    
    if (str == 0)
        return 0;
    
    while (str[i] == ' ' || str[i] == '\t')
        i++;
    
    while (str[i] == '-' || str[i] == '+') {
        if (str[i] == '-')
            sign = -sign;
        i++;
    }
    
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    
    return result * sign;
}
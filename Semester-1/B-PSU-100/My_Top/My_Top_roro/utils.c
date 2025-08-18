#include "my_top.h"

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

int my_atoi(char *str)
{
    int result = 0;
    int i = 0;
    int sign = 1;
    
    if (!str)
        return 0;
    if (str[0] == '-') {
        sign = -1;
        i = 1;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result * sign;
}

double my_atof(char *str)
{
    double result = 0.0;
    double decimal = 0.0;
    double divisor = 1.0;
    int i = 0;
    int sign = 1;
    int decimal_point = 0;
    
    if (!str)
        return 0.0;
    if (str[0] == '-') {
        sign = -1;
        i = 1;
    }
    
    while (str[i]) {
        if (str[i] == '.') {
            decimal_point = 1;
            i++;
            continue;
        }
        if (str[i] >= '0' && str[i] <= '9') {
            if (decimal_point) {
                divisor *= 10.0;
                decimal = decimal * 10.0 + (str[i] - '0');
            } else {
                result = result * 10.0 + (str[i] - '0');
            }
        }
        i++;
    }
    
    return sign * (result + decimal / divisor);
}
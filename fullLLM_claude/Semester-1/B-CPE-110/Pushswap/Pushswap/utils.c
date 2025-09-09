#include "push_swap.h"

int my_atoi(const char *str)
{
    int result = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-') {
        sign = -1;
        i = 1;
    } else if (str[0] == '+') {
        i = 1;
    }

    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return result * sign;
}

int is_valid_number(const char *str)
{
    int i = 0;

    if (!str || !str[0])
        return 0;

    if (str[0] == '-' || str[0] == '+')
        i = 1;

    if (!str[i])
        return 0;

    while (str[i]) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
        i++;
    }

    return 1;
}
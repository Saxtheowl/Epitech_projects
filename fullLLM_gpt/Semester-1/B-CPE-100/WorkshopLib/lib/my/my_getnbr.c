#include <limits.h>

int my_getnbr(char const *str)
{
    long result = 0;
    int sign = 1;
    int i = 0;

    if (str == 0)
        return 0;
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
           str[i] == '\r' || str[i] == '\v' || str[i] == '\f') {
        ++i;
    }
    while (str[i] == '+' || str[i] == '-') {
        if (str[i] == '-')
            sign = -sign;
        ++i;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        result = (result * 10) + (str[i] - '0');
        long signed_result = result * sign;
        if (signed_result > INT_MAX || signed_result < INT_MIN)
            return 0;
        ++i;
    }
    return (int)(result * sign);
}

#include "phoenix.h"

static int is_digit(char c)
{
    return c >= '0' && c <= '9';
}

static int is_space(char c)
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v';
}

int to_number(char const *str)
{
    long result = 0;
    int sign = 1;
    int digit_found = 0;

    if (!str) {
        return 0;
    }
    while (*str && is_space(*str)) {
        ++str;
    }
    while (*str == '+' || *str == '-') {
        if (*str == '-') {
            sign = -sign;
        }
        ++str;
    }
    while (*str && is_digit(*str)) {
        int digit = *str - '0';
        long limit = (sign == 1) ? 2147483647L : 2147483648L;

        if (result > (limit - digit) / 10) {
            return 0;
        }
        result = result * 10 + digit;
        digit_found = 1;
        ++str;
    }
    if (!digit_found) {
        return 0;
    }
    result *= sign;
    if (result < -2147483648L || result > 2147483647L) {
        return 0;
    }
    return (int)result;
}

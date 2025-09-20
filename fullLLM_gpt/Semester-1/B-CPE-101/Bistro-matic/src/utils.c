#include <unistd.h>
#include <stdlib.h>
#include "bistromatic.h"
#include "utils.h"

size_t my_strlen(char const *str)
{
    size_t len = 0;

    if (!str)
        return 0;
    while (str[len] != '\0')
        ++len;
    return len;
}

void my_putstr(char const *str)
{
    if (!str)
        return;
    write(1, str, my_strlen(str));
}

void my_puterr(char const *str)
{
    if (!str)
        return;
    write(2, str, my_strlen(str));
}

static int is_digit_char(char c)
{
    return c >= '0' && c <= '9';
}

int my_atoi(char const *str)
{
    int sign = 1;
    long value = 0;
    size_t i = 0;

    if (!str)
        return 0;
    while (str[i] != '\0' && is_space(str[i]))
        ++i;
    if (str[i] == '+' || str[i] == '-') {
        if (str[i] == '-')
            sign = -1;
        ++i;
    }
    while (str[i] != '\0' && is_digit_char(str[i])) {
        value = value * 10 + (str[i] - '0');
        ++i;
    }
    return (int)(value * sign);
}

int is_space(char c)
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f';
}

void fatal_error(char const *message)
{
    if (message)
        my_puterr(message);
    exit(ERROR_CODE);
}

void *my_malloc(size_t size)
{
    void *ptr = malloc(size);

    if (!ptr)
        fatal_error(ERROR_MSG);
    return ptr;
}

char *my_strndup(char const *src, size_t n)
{
    char *copy;

    copy = my_malloc(n + 1);
    for (size_t i = 0; i < n; ++i)
        copy[i] = src[i];
    copy[n] = '\0';
    return copy;
}

#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr(char const *str)
{
    if (!str)
        return;
    while (*str) {
        write(1, str, 1);
        ++str;
    }
}

size_t my_strlen(char const *str)
{
    size_t len = 0;

    if (!str)
        return 0;
    while (str[len] != '\0')
        ++len;
    return len;
}

int my_is_space(char c)
{
    return c == ' ' || c == '\t' || c == '\n' ||
           c == '\r' || c == '\v' || c == '\f';
}

char *my_strdup_range(char const *start, char const *end)
{
    size_t len = (size_t)(end - start);
    char *copy = malloc(len + 1);

    if (!copy)
        return NULL;
    for (size_t i = 0; i < len; ++i)
        copy[i] = start[i];
    copy[len] = '\0';
    return copy;
}

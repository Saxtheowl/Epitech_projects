#include "phoenix.h"

static int is_lower(char c)
{
    return c >= 'a' && c <= 'z';
}

static int is_upper(char c)
{
    return c >= 'A' && c <= 'Z';
}

static int is_digit_char(char c)
{
    return c >= '0' && c <= '9';
}

static int is_alphanumeric(char c)
{
    return is_lower(c) || is_upper(c) || is_digit_char(c);
}

static char to_upper_char(char c)
{
    if (is_lower(c)) {
        return (char)(c - ('a' - 'A'));
    }
    return c;
}

static char to_lower_char(char c)
{
    if (is_upper(c)) {
        return (char)(c + ('a' - 'A'));
    }
    return c;
}

char *my_strcapitalize(char *str)
{
    int new_word = 1;

    if (!str) {
        return NULL;
    }
    for (int i = 0; str[i] != '\0'; ++i) {
        if (is_alphanumeric(str[i])) {
            if (new_word) {
                str[i] = to_upper_char(str[i]);
                new_word = 0;
            } else {
                str[i] = to_lower_char(str[i]);
            }
        } else {
            new_word = 1;
        }
    }
    return str;
}

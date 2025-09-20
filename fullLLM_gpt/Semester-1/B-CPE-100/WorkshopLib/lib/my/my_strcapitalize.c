#include "my.h"

static int is_alpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

static int is_digit(char c)
{
    return c >= '0' && c <= '9';
}

char *my_strcapitalize(char *str)
{
    int new_word = 1;

    if (str == 0)
        return str;
    my_strlowcase(str);
    for (int i = 0; str[i] != '\0'; ++i) {
        if (is_alpha(str[i]) || is_digit(str[i])) {
            if (new_word && is_alpha(str[i]) && str[i] >= 'a' && str[i] <= 'z')
                str[i] = (char)(str[i] - 'a' + 'A');
            new_word = 0;
        } else {
            new_word = 1;
        }
    }
    return str;
}

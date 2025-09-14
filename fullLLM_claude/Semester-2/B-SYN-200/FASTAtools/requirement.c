#include <stdlib.h>

static int is_alphanum(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
}

static int is_letter(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

static char to_upper(char c)
{
    if (c >= 'a' && c <= 'z')
        return c - 32;
    return c;
}

static char to_lower(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c + 32;
    return c;
}

char *my_strcapitalize_synthesis(char *str)
{
    int i;
    int first_letter = 1;
    
    if (!str)
        return str;
    
    for (i = 0; str[i]; i++) {
        if (is_letter(str[i])) {
            if (first_letter) {
                str[i] = to_upper(str[i]);
                first_letter = 0;
            } else {
                str[i] = to_lower(str[i]);
            }
        } else if (!is_alphanum(str[i])) {
            first_letter = 1;
        }
    }
    
    return str;
}
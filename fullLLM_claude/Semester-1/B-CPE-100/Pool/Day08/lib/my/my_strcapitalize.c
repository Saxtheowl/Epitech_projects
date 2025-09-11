/*
** EPITECH PROJECT, 2024
** Day06 - B-CPE-100
** File description:
** my_strcapitalize.c
*/

static int is_alphanum(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || 
            (c >= '0' && c <= '9'));
}

static int is_alpha(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

static int is_lower(char c)
{
    return (c >= 'a' && c <= 'z');
}

static int is_upper(char c)
{
    return (c >= 'A' && c <= 'Z');
}

char *my_strcapitalize(char *str)
{
    int i = 0;
    int new_word = 1;

    while (str[i] != '\0') {
        if (is_alphanum(str[i])) {
            if (new_word && is_alpha(str[i])) {
                if (is_lower(str[i]))
                    str[i] = str[i] - ('a' - 'A');
                new_word = 0;
            } else if (!new_word && is_upper(str[i])) {
                str[i] = str[i] + ('a' - 'A');
            }
        } else {
            new_word = 1;
        }
        i++;
    }

    return str;
}
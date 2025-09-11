/*
** EPITECH PROJECT, 2024
** Day06 - B-CPE-100
** File description:
** my_str_isprintable.c
*/

static int is_printable(char c)
{
    return (c >= 32 && c <= 126);
}

int my_str_isprintable(char const *str)
{
    int i = 0;

    if (str[0] == '\0')
        return 1;

    while (str[i] != '\0') {
        if (!is_printable(str[i]))
            return 0;
        i++;
    }

    return 1;
}
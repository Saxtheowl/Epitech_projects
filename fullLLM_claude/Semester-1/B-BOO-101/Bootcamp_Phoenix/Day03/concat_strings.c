/*
** EPITECH PROJECT, 2024
** Day03 - Bootcamp Phoenix
** File description:
** concat_strings.c
*/

static int my_strlen(char const *str)
{
    int len = 0;

    while (str[len] != '\0')
        len++;
    return len;
}

char *concat_strings(char *dest, char const *src)
{
    int dest_len = my_strlen(dest);
    int i = 0;

    while (src[i] != '\0') {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';

    return dest;
}
/*
** EPITECH PROJECT, 2024
** reverse_string
** File description:
** Reverse a string by swapping characters two by two
*/

static int my_strlen(char *str)
{
    int len = 0;

    while (str[len] != '\0')
        len++;
    return len;
}

char *reverse_string(char *str)
{
    int len = my_strlen(str);
    int i = 0;
    char temp;

    while (i < len / 2) {
        temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
        i++;
    }
    return str;
}
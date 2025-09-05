/*
** EPITECH PROJECT, 2025
** Cesar
** File description:
** caesar cipher functions
*/

#include "cesar.h"

char caesar_encrypt_char(char c, int key)
{
    if (c >= 'A' && c <= 'Z') {
        int shifted = (c - 'A' + key) % 26;
        if (shifted < 0)
            shifted += 26;
        return shifted + 'A';
    }
    if (c >= 'a' && c <= 'z') {
        int shifted = (c - 'a' + key) % 26;
        if (shifted < 0)
            shifted += 26;
        return shifted + 'a';
    }
    return c;
}

char *caesar_encrypt_string(char *str, int key)
{
    char *result;
    int i = 0;

    if (!str)
        return NULL;
    result = malloc(sizeof(char) * (my_strlen(str) + 1));
    if (!result)
        return NULL;
    while (str[i]) {
        result[i] = caesar_encrypt_char(str[i], key);
        i++;
    }
    result[i] = '\0';
    return result;
}
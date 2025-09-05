/*
** EPITECH PROJECT, 2025
** Fridge
** File description:
** utils
*/

#include "fridge.h"

int my_strlen(char *str)
{
    int len = 0;

    if (!str)
        return 0;
    while (str[len])
        len++;
    return len;
}

char *my_strcpy(char *dest, char *src)
{
    int i = 0;

    if (!dest || !src)
        return dest;
    while (src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

int my_strcmp(char *s1, char *s2)
{
    int i = 0;

    if (!s1 || !s2)
        return -1;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return s1[i] - s2[i];
}

char *my_strdup(char *src)
{
    char *dest;
    int i = 0;

    if (!src)
        return NULL;
    dest = malloc(sizeof(char) * (my_strlen(src) + 1));
    if (!dest)
        return NULL;
    while (src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

int my_atoi(char *str)
{
    int result = 0;
    int sign = 1;
    int i = 0;

    if (!str)
        return 0;
    if (str[0] == '-') {
        sign = -1;
        i = 1;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result * sign;
}

char *my_itoa(int n)
{
    char *str;
    int len = 0;
    int temp = n;

    if (n == 0)
        len = 1;
    else {
        while (temp > 0) {
            temp /= 10;
            len++;
        }
    }
    str = malloc(sizeof(char) * (len + 1));
    if (!str)
        return NULL;
    str[len] = '\0';
    if (n == 0)
        str[0] = '0';
    else {
        while (n > 0) {
            str[--len] = (n % 10) + '0';
            n /= 10;
        }
    }
    return str;
}

void my_putstr(char *str)
{
    if (str)
        write(STDOUT_FILENO, str, my_strlen(str));
}

void my_putchar(char c)
{
    write(STDOUT_FILENO, &c, 1);
}
/*
** EPITECH PROJECT, 2024
** My_ls
** File description:
** Utility functions for my_ls
*/

#include "../include/my_ls.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr(const char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i]) {
        my_putchar(str[i]);
        i++;
    }
}

void my_putnbr(int nb)
{
    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    if (nb >= 10)
        my_putnbr(nb / 10);
    my_putchar('0' + nb % 10);
}

int my_strlen(const char *str)
{
    int len = 0;

    if (!str)
        return 0;
    while (str[len])
        len++;
    return len;
}

int my_strcmp(const char *s1, const char *s2)
{
    int i = 0;

    if (!s1 || !s2)
        return 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return s1[i] - s2[i];
}

void my_strcpy(char *dest, const char *src)
{
    int i = 0;

    if (!dest || !src)
        return;
    while (src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

char *my_strcat(char *dest, const char *src)
{
    int dest_len = my_strlen(dest);
    int i = 0;

    if (!dest || !src)
        return dest;
    while (src[i]) {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
    return dest;
}

char *my_strdup(const char *src)
{
    char *dup;
    int len;
    int i = 0;

    if (!src)
        return NULL;
    len = my_strlen(src);
    dup = malloc(len + 1);
    if (!dup)
        return NULL;
    while (src[i]) {
        dup[i] = src[i];
        i++;
    }
    dup[i] = '\0';
    return dup;
}

void free_file_list(file_info_t *files)
{
    file_info_t *current = files;
    file_info_t *next;

    while (current) {
        next = current->next;
        free(current->name);
        free(current->full_path);
        free(current);
        current = next;
    }
}
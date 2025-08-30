/*
** EPITECH PROJECT, 2025
** WorkshopLib_roro
** File description:
** my_strcpy
*/

char *my_strcpy(char *dst, const char *src)
{
    char *p;

    p = dst;
    while (*src) {
        *p = *src;
        p += 1;
        src += 1;
    }
    *p = '\0';
    return dst;
}

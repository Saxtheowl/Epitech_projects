/*
** EPITECH PROJECT, 2024
** Day07 - B-CPE-100
** File description:
** my_strncat.c
*/

char *my_strncat(char *dest, char const *src, int nb)
{
    int dest_len = 0;
    int i = 0;
    
    while (dest[dest_len] != '\0') {
        dest_len++;
    }
    
    while (src[i] != '\0' && i < nb) {
        dest[dest_len + i] = src[i];
        i++;
    }
    
    dest[dest_len + i] = '\0';
    
    return dest;
}
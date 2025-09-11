/*
** EPITECH PROJECT, 2024
** Day08 - B-CPE-100
** File description:
** convert_base.c - TASK 05
*/

#include <stdlib.h>
#include <stddef.h>

int my_strlen(char const *str);
int my_getnbr_base(char const *str, char const *base);
int my_putnbr_base(int nbr, char const *base);

static int count_digits_in_base(int nbr, int base_len)
{
    int count = 0;
    
    if (nbr == 0)
        return 1;
    
    if (nbr < 0) {
        count = 1;
        nbr = -nbr;
    }
    
    while (nbr > 0) {
        nbr /= base_len;
        count++;
    }
    
    return count;
}

static void fill_result(char *result, int nbr, char const *base_to, int base_len)
{
    int i = 0;
    int sign = 1;
    
    if (nbr < 0) {
        result[0] = '-';
        i = 1;
        nbr = -nbr;
        sign = -1;
    }
    
    if (nbr == 0) {
        result[i] = base_to[0];
        result[i + 1] = '\0';
        return;
    }
    
    int len = count_digits_in_base(nbr * sign, base_len);
    int pos = len - 1;
    
    while (nbr > 0) {
        result[pos] = base_to[nbr % base_len];
        nbr /= base_len;
        pos--;
    }
    
    result[len] = '\0';
}

char *convert_base(char const *nbr, char const *base_from, char const *base_to)
{
    int decimal_value;
    int base_to_len;
    int result_len;
    char *result;
    
    if (nbr == NULL || base_from == NULL || base_to == NULL)
        return NULL;
    
    decimal_value = my_getnbr_base(nbr, base_from);
    base_to_len = my_strlen(base_to);
    
    if (base_to_len == 0)
        return NULL;
    
    result_len = count_digits_in_base(decimal_value, base_to_len);
    result = malloc(sizeof(char) * (result_len + 1));
    
    if (result == NULL)
        return NULL;
    
    fill_result(result, decimal_value, base_to, base_to_len);
    
    return result;
}
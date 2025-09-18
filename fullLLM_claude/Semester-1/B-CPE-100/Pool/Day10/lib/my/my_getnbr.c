/*
** EPITECH PROJECT, 2024
** Day07 - B-CPE-100
** File description:
** my_getnbr.c
*/

int my_getnbr(char const *str)
{
    int result = 0;
    int sign = 1;
    int i = 0;
    
    while (str[i] == '-' || str[i] == '+') {
        if (str[i] == '-')
            sign = -sign;
        i++;
    }
    
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    
    return result * sign;
}
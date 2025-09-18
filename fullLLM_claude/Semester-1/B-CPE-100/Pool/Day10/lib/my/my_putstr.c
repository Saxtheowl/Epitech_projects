/*
** EPITECH PROJECT, 2024
** Day07 - B-CPE-100
** File description:
** my_putstr.c
*/

void my_putchar(char c);

int my_putstr(char const *str)
{
    int i = 0;
    
    while (str[i] != '\0') {
        my_putchar(str[i]);
        i++;
    }
    return 0;
}
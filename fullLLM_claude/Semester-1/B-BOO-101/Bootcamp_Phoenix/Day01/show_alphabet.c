/*
** EPITECH PROJECT, 2024
** show_alphabet
** File description:
** Display lowercase alphabet in ascending order
*/

int my_putchar(char c);

int show_alphabet(void)
{
    char c = 'a';

    while (c <= 'z') {
        my_putchar(c);
        c++;
    }
    return 0;
}
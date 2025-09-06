/*
** EPITECH PROJECT, 2025
** ftrace
** File description:
** Simple test program for ftrace
*/

#include <stdio.h>
#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr(char *str)
{
    int i = 0;

    while (str[i]) {
        my_putchar(str[i]);
        i++;
    }
}

int main(void)
{
    my_putstr("Hello");
    my_putchar('\n');
    printf("World\n");
    return 0;
}
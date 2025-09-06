/*
** EPITECH PROJECT, 2025
** Day05 - String Module
** File description:
** Test main function from PDF example
*/

#include <stdio.h>
#include "string.h"

int main(void)
{
    string_t s;

    string_init(&s, "Hello World");
    printf("%s\n", s.str);
    string_destroy(&s);
    return (0);
}
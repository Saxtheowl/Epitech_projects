/*
** EPITECH PROJECT, 2025
** FazzBizz
** File description:
** Utility functions for fazzbizz
*/

#include "fazzbizz.h"

void print_error(void)
{
    write(2, "Error: the second parameter must be greater than the first one.\n", 64);
}
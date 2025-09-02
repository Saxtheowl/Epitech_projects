/*
** EPITECH PROJECT, 2025
** NmObjdump
** File description:
** Utility functions
*/

#include "nm_objdump.h"

void print_error(const char *program, const char *message)
{
    fprintf(stderr, "%s: %s\n", program, message);
}
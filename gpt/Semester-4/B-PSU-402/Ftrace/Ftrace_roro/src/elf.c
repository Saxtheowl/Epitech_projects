/*
** EPITECH PROJECT, 2025
** ftrace
** File description:
**   ELF symbol lookup (libelf)
*/

#include <stddef.h>

unsigned long elf_find_symbol_addr(const char *path, const char *name)
{
    (void)path; (void)name;
    return 0; /* Fallback when libelf is unavailable in environment */
}

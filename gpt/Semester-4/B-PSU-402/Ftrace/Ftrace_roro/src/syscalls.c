/*
** EPITECH PROJECT, 2025
** ftrace
** File description:
**   syscall decoding (subset)
*/

#include <stdio.h>

typedef struct { long n; const char *name; } sc_t;

static const sc_t table[] = {
    {0, "read"}, {1, "write"}, {2, "open"}, {3, "close"},
    {60, "exit"}, {231, "exit_group"}, {257, "openat"},
};

const char *syscall_name(long n)
{
    for (unsigned i = 0; i < sizeof(table)/sizeof(table[0]); ++i)
        if (table[i].n == n) return table[i].name;
    return "unknown";
}

void print_syscall(long n, unsigned long a0, unsigned long a1,
    unsigned long a2, long ret)
{
    printf("Syscall %s (0x%lx, 0x%lx, 0x%lx) = 0x%lx\n",
        syscall_name(n), a0, a1, a2, (unsigned long)ret);
}


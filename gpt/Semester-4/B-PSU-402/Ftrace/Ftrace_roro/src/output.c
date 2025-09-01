/*
** EPITECH PROJECT, 2025
** ftrace
** File description:
**   output helpers
*/

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include "ftrace.h"

void print_enter_main(const traced_t *t)
{
    if (t->main_addr)
        printf("Entering function main at 0x%lx\n", t->main_addr);
}

void print_signal(int sig)
{
    const char *n = strsignal(sig);
    if (!n) n = "unknown";
    printf("Received signal %s\n", n);
}

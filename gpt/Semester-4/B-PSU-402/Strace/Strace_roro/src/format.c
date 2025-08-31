/*
** EPITECH PROJECT, 2025
** Strace_roro
** File description:
** formatting
*/

#include <stdio.h>
#include <string.h>
#include "strace.h"

static void print_arg_hex(unsigned long v)
{
    printf("0x%lx", v);
}

static void print_arg_s(unsigned long v, pid_t pid)
{
    char buf[256];

    if (v == 0) {
        printf("NULL");
        return;
    }
    if (read_string(pid, v, buf, sizeof(buf)) == 0 && buf[0] != '\0') {
        /* crude heuristic: show as string if printable */
        size_t i = 0;
        int ok = 1;
        for (i = 0; buf[i] && i < sizeof(buf); ++i) {
            if ((unsigned char)buf[i] < 32 || (unsigned char)buf[i] >= 127) {
                ok = 0; break;
            }
        }
        if (ok) {
            printf("\"%s\"", buf);
            return;
        }
    }
    /* Fallback: show pointer in hex like strace */
    printf("0x%lx", v);
}

static void print_arg_kind(arg_kind_t k, unsigned long v, bool opt_s, pid_t pid)
{
    if (!opt_s) {
        print_arg_hex(v);
        return;
    }
    if (k == ARG_INT)
        printf("%ld", (long)v);
    else if (k == ARG_STR)
        print_arg_s(v, pid);
    else
        printf("0x%lx", v);
}

void print_entry(long id, unsigned long args[6], bool opt_s, pid_t pid)
{
    const call_t *c = sys_get(id);
    int i;

    if (c && c->name)
        printf("%s(", c->name);
    else
        printf("sys_%ld(", id);
    for (i = 0; i < (c ? c->nargs : 6); ++i) {
        if (i > 0)
            printf(", ");
        if (c)
            print_arg_kind(c->args[i], args[i], opt_s, pid);
        else
            print_arg_kind(ARG_PTR, args[i], opt_s, pid);
    }
    printf(") = ");
}

void print_exit(long id, unsigned long ret, bool opt_s)
{
    const call_t *c = sys_get(id);
    if (c && (strcmp(c->name, "exit") == 0 || strcmp(c->name, "exit_group") == 0)) {
        printf("?\n");
        fflush(stdout);
        return;
    }
    if (opt_s)
        printf("%ld\n", (long)ret);
    else
        printf("0x%lx\n", ret);
    fflush(stdout);
}

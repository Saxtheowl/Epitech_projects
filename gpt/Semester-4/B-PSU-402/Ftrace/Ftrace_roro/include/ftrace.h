/*
** EPITECH PROJECT, 2025
** ftrace
** File description:
**   Public interfaces
*/

#ifndef FTRACE_H
#define FTRACE_H

#include <stddef.h>
#include <sys/types.h>

typedef struct traced_s {
    const char *prog;
    char **argv;
    unsigned long main_addr;
    pid_t pid;
} traced_t;

/* args.c */
int parse_args(int ac, char **av, traced_t *t);
void print_usage(void);

/* tracer.c */
int run_trace(traced_t *t);

/* syscalls.c */
const char *syscall_name(long n);
void print_syscall(long n, unsigned long a0, unsigned long a1,
    unsigned long a2, long ret);

/* elf.c */
unsigned long elf_find_symbol_addr(const char *path, const char *name);

/* output.c */
void print_enter_main(const traced_t *t);
void print_signal(int sig);

/* strings.c */
int my_strcmp(const char *a, const char *b);

#define EXIT_ERR 84

#endif /* FTRACE_H */

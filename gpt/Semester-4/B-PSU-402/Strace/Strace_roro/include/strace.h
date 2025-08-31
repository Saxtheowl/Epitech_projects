/*
** EPITECH PROJECT, 2025
** Strace_roro
** File description:
** header
*/

#ifndef STRACE_H
    #define STRACE_H

    #include <sys/types.h>
    #include <sys/ptrace.h>
    #include <sys/wait.h>
    #include <sys/user.h>
    #include <signal.h>
    #include <errno.h>
    #include <stdbool.h>
    #include <stddef.h>

    typedef struct options_s {
        bool opt_s;
        pid_t pid;
        char const **cmd;
    } options_t;

    typedef enum {
        ARG_INT = 0,
        ARG_STR = 1,
        ARG_PTR = 2
    } arg_kind_t;

    typedef struct call_s {
        const char *name;
        int nargs;
        arg_kind_t args[6];
    } call_t;

    /* args */
    int parse_args(int ac, char const **av, options_t *opt);
    void print_usage(void);

    /* tracer */
    int trace_exec(const options_t *opt);
    int trace_attach(const options_t *opt);

    /* arch */
    long arch_get_syscall(pid_t pid);
    void arch_get_args(pid_t pid, unsigned long args[6]);
    unsigned long arch_get_ret(pid_t pid);

    /* mem */
    int read_string(pid_t pid, unsigned long addr, char *buf, size_t max);

    /* syscalls */
    const call_t *sys_get(long id);

    /* format */
    void print_entry(long id, unsigned long args[6], bool opt_s, pid_t pid);
    void print_exit(long id, unsigned long ret, bool opt_s);

#endif /* STRACE_H */

/*
** EPITECH PROJECT, 2025
** Strace_roro
** File description:
** tracer
*/

#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/user.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "strace.h"

static int loop_trace(pid_t pid, int opt_s)
{
    int status;
    while (1) {
        /* Inspect current instruction */
        struct user_regs_struct regs;
        long word;
        unsigned short op = 0;

        if (ptrace(PTRACE_GETREGS, pid, 0, &regs) == -1)
            return 84;
        errno = 0;
        word = ptrace(PTRACE_PEEKDATA, pid, (void *)regs.rip, 0);
        if (errno == 0)
            op = (unsigned short)(word & 0xFFFF);

        if (op == 0x050F) {
            /* syscall about to execute: entry */
            long sc_entry = (long)regs.rax;
            unsigned long args[6];
            unsigned long ret;
            arch_get_args(pid, args);
            print_entry(sc_entry, args, opt_s, pid);

            /* single-step to execute syscall */
            if (ptrace(PTRACE_SINGLESTEP, pid, 0, 0) == -1)
                return 84;
            if (waitpid(pid, &status, 0) == -1)
                return 84;
            if (WIFEXITED(status))
                break;
            if (!WIFSTOPPED(status))
                continue;
            /* read return value after syscall */
            ret = arch_get_ret(pid);
            print_exit(sc_entry, ret, opt_s);
        }

        /* advance by one instruction */
        if (ptrace(PTRACE_SINGLESTEP, pid, 0, 0) == -1)
            return 84;
        if (waitpid(pid, &status, 0) == -1)
            return 84;
        if (WIFEXITED(status))
            break;
        if (!WIFSTOPPED(status))
            continue;
    }
    return 0;
}

int trace_exec(const options_t *opt)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
        return 84;
    if (pid == 0) {
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        raise(SIGSTOP);
        execvp((char const *)opt->cmd[0], (char *const *)opt->cmd);
        _exit(1);
    }
    if (waitpid(pid, &status, 0) == -1)
        return 84;
    return loop_trace(pid, opt->opt_s);
}

int trace_attach(const options_t *opt)
{
    int status;

    if (ptrace(PTRACE_ATTACH, opt->pid, 0, 0) == -1) {
        perror("ptrace");
        return 84;
    }
    if (waitpid(opt->pid, &status, 0) == -1)
        return 84;
    return loop_trace(opt->pid, opt->opt_s);
}

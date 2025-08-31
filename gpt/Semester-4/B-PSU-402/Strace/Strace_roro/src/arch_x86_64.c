/*
** EPITECH PROJECT, 2025
** Strace_roro
** File description:
** arch x86_64 helpers
*/

#include <sys/ptrace.h>
#include <sys/user.h>
#include "strace.h"

long arch_get_syscall(pid_t pid)
{
    struct user_regs_struct r;

    ptrace(PTRACE_GETREGS, pid, 0, &r);
    /* With single-stepping, syscall number is in rax before executing */
    return (long)r.rax;
}

void arch_get_args(pid_t pid, unsigned long args[6])
{
    struct user_regs_struct r;

    ptrace(PTRACE_GETREGS, pid, 0, &r);
    args[0] = (unsigned long)r.rdi;
    args[1] = (unsigned long)r.rsi;
    args[2] = (unsigned long)r.rdx;
    args[3] = (unsigned long)r.r10;
    args[4] = (unsigned long)r.r8;
    args[5] = (unsigned long)r.r9;
}

unsigned long arch_get_ret(pid_t pid)
{
    struct user_regs_struct r;

    ptrace(PTRACE_GETREGS, pid, 0, &r);
    return (unsigned long)r.rax;
}

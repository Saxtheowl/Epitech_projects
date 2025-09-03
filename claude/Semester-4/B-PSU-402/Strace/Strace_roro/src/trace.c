/*
** EPITECH PROJECT, 2025
** Strace
** File description:
** Process tracing functions
*/

#include "strace.h"

static long get_register_value(pid_t pid, int reg)
{
    return ptrace(PTRACE_PEEKUSER, pid, 8 * reg, NULL);
}

static void get_syscall_args(pid_t pid, long *args)
{
    args[0] = get_register_value(pid, RDI);
    args[1] = get_register_value(pid, RSI);
    args[2] = get_register_value(pid, RDX);
    args[3] = get_register_value(pid, R10);
    args[4] = get_register_value(pid, R8);
    args[5] = get_register_value(pid, R9);
}

static int wait_for_syscall(pid_t pid)
{
    int status = 0;

    while (1) {
        ptrace(PTRACE_CONT, pid, NULL, NULL);
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status) || WIFSIGNALED(status))
            return 1;
        
        if (WIFSTOPPED(status) && WSTOPSIG(status) == SIGTRAP)
            return 0;
    }
}

int trace_process(pid_t pid, int detailed)
{
    int status = 0;
    long syscall_num = 0;
    long args[MAX_ARGS];
    long ret_value = 0;
    int in_syscall = 0;

    waitpid(pid, &status, 0);
    ptrace(PTRACE_SETOPTIONS, pid, NULL, PTRACE_O_TRACESYSGOOD);
    
    while (1) {
        if (wait_for_syscall(pid) != 0)
            break;
        
        syscall_num = get_register_value(pid, ORIG_RAX);
        
        if (!in_syscall) {
            get_syscall_args(pid, args);
            in_syscall = 1;
        } else {
            ret_value = get_register_value(pid, RAX);
            print_syscall(syscall_num, args, ret_value, detailed);
            in_syscall = 0;
        }
    }
    
    return 0;
}

int attach_to_pid(pid_t pid)
{
    if (ptrace(PTRACE_ATTACH, pid, NULL, NULL) == -1) {
        perror("ptrace attach");
        return -1;
    }
    return 0;
}

pid_t execute_command(char **command)
{
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return -1;
    }
    
    if (pid == 0) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execvp(command[0], command);
        perror("execvp");
        exit(84);
    }
    
    return pid;
}

int run_strace(strace_t *strace)
{
    pid_t pid = 0;

    if (strace->attach_mode) {
        if (attach_to_pid(strace->target_pid) != 0)
            return -1;
        pid = strace->target_pid;
    } else {
        pid = execute_command(strace->command);
        if (pid == -1)
            return -1;
    }
    
    return trace_process(pid, strace->detailed_mode);
}
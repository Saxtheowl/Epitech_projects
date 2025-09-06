/*
** EPITECH PROJECT, 2025
** ftrace
** File description:
** Ptrace utilities and child process handling
*/

#include "ftrace.h"

int setup_child(char **argv)
{
    if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1) {
        print_error("Failed to set up tracing");
        return EXIT_ERROR;
    }

    if (execvp(argv[0], argv) == -1) {
        print_error("Failed to execute command");
        return EXIT_ERROR;
    }

    return EXIT_SUCCESS;
}

static int handle_syscall(ftrace_t *ftrace, struct user_regs_struct *regs)
{
    if (!ftrace->in_syscall) {
        ftrace->in_syscall = 1;
        ftrace->last_syscall = regs->orig_rax;
        
        printf("Syscall %s (", get_syscall_name(regs->orig_rax));
        print_syscall_args(regs, regs->orig_rax);
        printf(")");
        fflush(stdout);
    } else {
        printf(" = 0x%llx\n", regs->rax);
        ftrace->in_syscall = 0;
    }
    return 0;
}

static int handle_function_call(ftrace_t *ftrace, unsigned long rip)
{
    symbol_t *symbol = find_symbol(ftrace->symbols, rip);
    
    if (symbol) {
        printf("Entering function %s at 0x%lx\n", symbol->name, rip);
    } else {
        printf("Entering function func_0x%lx@%s at 0x%lx\n", 
               rip, ftrace->binary_path, rip);
    }
    return 0;
}

int trace_child(ftrace_t *ftrace)
{
    struct user_regs_struct regs;
    int wait_status;

    waitpid(ftrace->child_pid, &wait_status, 0);

    if (ptrace(PTRACE_SETOPTIONS, ftrace->child_pid, 0, 
               PTRACE_O_TRACESYSGOOD | PTRACE_O_TRACEEXEC) == -1) {
        print_error("Failed to set ptrace options");
        return EXIT_ERROR;
    }

    while (1) {
        if (ptrace(PTRACE_SYSCALL, ftrace->child_pid, 0, 0) == -1) {
            if (errno == ESRCH)
                break;
            print_error("Failed to continue tracing");
            return EXIT_ERROR;
        }

        waitpid(ftrace->child_pid, &wait_status, 0);

        if (WIFEXITED(wait_status) || WIFSIGNALED(wait_status))
            break;

        if (WIFSTOPPED(wait_status)) {
            int sig = WSTOPSIG(wait_status);
            
            if (sig == SIGTRAP) {
                if (wait_status >> 8 == (SIGTRAP | (PTRACE_EVENT_EXEC << 8))) {
                    continue;
                }
                
                if (ptrace(PTRACE_GETREGS, ftrace->child_pid, 0, &regs) == -1) {
                    print_error("Failed to get registers");
                    continue;
                }

                if (wait_status >> 8 == (SIGTRAP | 0x80)) {
                    handle_syscall(ftrace, &regs);
                } else {
                    handle_function_call(ftrace, regs.rip);
                }
            } else {
                printf("Received signal %s\n", strsignal(sig));
                if (ptrace(PTRACE_SYSCALL, ftrace->child_pid, 0, sig) == -1) {
                    print_error("Failed to deliver signal");
                    break;
                }
                continue;
            }
        }
    }

    return EXIT_SUCCESS;
}
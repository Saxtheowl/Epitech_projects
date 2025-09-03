/*
** EPITECH PROJECT, 2025
** Strace
** File description:
** System call tracer header
*/

#ifndef STRACE_H_
    #define STRACE_H_

    #define _GNU_SOURCE
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/ptrace.h>
    #include <sys/wait.h>
    #include <sys/user.h>
    #include <sys/syscall.h>
    #include <errno.h>
    #include <signal.h>
    #include <sys/reg.h>

    #define MAX_ARGS 6
    #define BUFFER_SIZE 1024

    typedef struct strace_s {
        pid_t target_pid;
        int detailed_mode;
        int attach_mode;
        char **command;
    } strace_t;

    typedef struct syscall_info_s {
        long number;
        const char *name;
        int nb_args;
    } syscall_info_t;

    int parse_arguments(int argc, char **argv, strace_t *strace);
    void display_help(void);
    int run_strace(strace_t *strace);
    int trace_process(pid_t pid, int detailed);
    int attach_to_pid(pid_t pid);
    pid_t execute_command(char **command);
    void print_syscall(long syscall_num, long *args, long ret, int detailed);
    const char *get_syscall_name(long syscall_num);
    void print_detailed_args(long syscall_num, long *args);
    void print_hex_args(long *args, int nb_args);

#endif /* !STRACE_H_ */
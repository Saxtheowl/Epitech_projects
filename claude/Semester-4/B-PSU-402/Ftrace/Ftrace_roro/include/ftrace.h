/*
** EPITECH PROJECT, 2025
** ftrace
** File description:
** Header file for ftrace project
*/

#pragma once

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/user.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>

#define EXIT_SUCCESS    0
#define EXIT_ERROR      84

#define SYSCALL_TABLE_SIZE 400

typedef struct symbol_s {
    char *name;
    unsigned long address;
    struct symbol_s *next;
} symbol_t;

typedef struct ftrace_s {
    pid_t child_pid;
    int status;
    symbol_t *symbols;
    char *binary_path;
    int in_syscall;
    unsigned long last_syscall;
} ftrace_t;

// Main ftrace functions
int ftrace_main(char **argv);
int trace_child(ftrace_t *ftrace);
int setup_child(char **argv);

// Symbol table functions
int load_symbols(ftrace_t *ftrace);
symbol_t *find_symbol(symbol_t *symbols, unsigned long addr);
void free_symbols(symbol_t *symbols);

// Syscall functions
const char *get_syscall_name(int syscall_num);
void print_syscall_args(struct user_regs_struct *regs, int syscall_num);

// Signal handling
void handle_signal(int sig);

// Ptrace utilities
int handle_instruction(ftrace_t *ftrace, struct user_regs_struct *regs);
int is_function_call(unsigned long instruction);
int is_function_ret(unsigned long instruction);

// Utility functions
void print_usage(void);
void print_error(const char *message);
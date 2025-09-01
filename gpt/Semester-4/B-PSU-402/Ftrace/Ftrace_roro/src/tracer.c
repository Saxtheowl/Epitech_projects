/*
** EPITECH PROJECT, 2025
** ftrace
** File description:
**   ptrace tracer (syscalls + signals)
*/

#define _GNU_SOURCE
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/reg.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include "ftrace.h"
#include <limits.h>
#include <string.h>

static unsigned long read_word(pid_t pid, unsigned long addr)
{
    errno = 0;
    unsigned long w = (unsigned long)ptrace(PTRACE_PEEKTEXT, pid, addr, 0);
    (void)errno;
    return w;
}

static unsigned char read_byte(pid_t pid, unsigned long addr)
{
    unsigned long base = addr & ~(sizeof(long) - 1);
    unsigned long w = read_word(pid, base);
    unsigned shift = (unsigned)(addr - base) * 8;
    return (unsigned char)((w >> shift) & 0xFF);
}

static int maps_basename_for_addr(pid_t pid, unsigned long addr,
    char *out, size_t cap)
{
    char path[64];
    char line[PATH_MAX + 128];
    FILE *fp = NULL;

    snprintf(path, sizeof(path), "/proc/%d/maps", (int)pid);
    fp = fopen(path, "r");
    if (!fp) {
        out[0] = '\0';
        return -1;
    }
    while (fgets(line, sizeof(line), fp)) {
        unsigned long start = 0, end = 0, off = 0;
        char perms[8];
        char map_path[PATH_MAX];
        map_path[0] = '\0';
        /* sample: start-end perms offset dev inode pathname */
        sscanf(line, "%lx-%lx %7s %lx %*s %*s %s",
            &start, &end, perms, &off, map_path);
        if (addr >= start && addr < end) {
            const char *base = map_path;
            size_t len = strlen(map_path);
            size_t i = 0;
            for (i = len; i > 0; --i) {
                if (map_path[i - 1] == '/') { base = &map_path[i]; break; }
            }
            if (base && *base) {
                strncpy(out, base, cap - 1);
                out[cap - 1] = '\0';
            } else {
                out[0] = '\0';
            }
            fclose(fp);
            return 0;
        }
    }
    fclose(fp);
    out[0] = '\0';
    return -1;
}

static void print_enter_desc(pid_t pid, unsigned long tgt)
{
    char base[PATH_MAX];
    if (maps_basename_for_addr(pid, tgt, base, sizeof(base)) == 0
        && base[0] != '\0')
        printf("Entering function func_0x%lx@%s\n", tgt, base);
    else
        printf("Entering function func_0x%lx\n", tgt);
}

static void print_leave_desc(pid_t pid, unsigned long tgt)
{
    char base[PATH_MAX];
    if (maps_basename_for_addr(pid, tgt, base, sizeof(base)) == 0
        && base[0] != '\0')
        printf("Leaving function func_0x%lx@%s\n", tgt, base);
    else
        printf("Leaving function func_0x%lx\n", tgt);
}

static int trace_loop(traced_t *t)
{
    int status = 0;
    struct user_regs_struct prev = {0};
    int prev_valid = 0;
    unsigned long call_stack[256];
    int sp = 0;

    while (1) {
        if (waitpid(t->pid, &status, 0) < 0)
            return -1;
        if (WIFEXITED(status) || WIFSIGNALED(status))
            break;
        if (WIFSTOPPED(status)) {
            int sig = WSTOPSIG(status);
            struct user_regs_struct r;
            if (ptrace(PTRACE_GETREGS, t->pid, 0, &r) != 0) {
                ptrace(PTRACE_SINGLESTEP, t->pid, 0, 0);
                continue;
            }
            /* detect syscall (0F 05) */
            if (read_byte(t->pid, r.rip - 2) == 0x05
                && read_byte(t->pid, r.rip - 3) == 0x0F) {
                if (prev_valid) {
                    print_syscall((long)prev.rax, (unsigned long)prev.rdi,
                        (unsigned long)prev.rsi, (unsigned long)prev.rdx,
                        (long)r.rax);
                }
            }
            /* detect call rel32 (E8 disp32) */
            if (read_byte(t->pid, r.rip - 5) == 0xE8) {
                unsigned char b1 = read_byte(t->pid, r.rip - 4);
                unsigned char b2 = read_byte(t->pid, r.rip - 3);
                unsigned char b3 = read_byte(t->pid, r.rip - 2);
                unsigned char b4 = read_byte(t->pid, r.rip - 1);
                unsigned long off = (unsigned long)(int)((b1) | (b2<<8)
                    | (b3<<16) | (b4<<24));
                unsigned long tgt = r.rip + off;
                if (sp < (int)(sizeof(call_stack)/sizeof(call_stack[0]))) {
                    call_stack[sp++] = tgt;
                }
                print_enter_desc(t->pid, tgt);
            } else if (read_byte(t->pid, r.rip - 6) == 0xFF
                && read_byte(t->pid, r.rip - 5) == 0x15) {
                /* detect call qword ptr [RIP+disp32] (PLT/GOT) */
                unsigned char d1 = read_byte(t->pid, r.rip - 4);
                unsigned char d2 = read_byte(t->pid, r.rip - 3);
                unsigned char d3 = read_byte(t->pid, r.rip - 2);
                unsigned char d4 = read_byte(t->pid, r.rip - 1);
                unsigned long disp = (unsigned long)(int)((d1) | (d2<<8)
                    | (d3<<16) | (d4<<24));
                unsigned long ptr_addr = r.rip + disp;
                unsigned long tgt = read_word(t->pid, ptr_addr);
                if (sp < (int)(sizeof(call_stack)/sizeof(call_stack[0]))) {
                    call_stack[sp++] = tgt;
                }
                print_enter_desc(t->pid, tgt);
            }
            /* detect ret (C3/CB) */
            if (read_byte(t->pid, r.rip - 1) == 0xC3
                || read_byte(t->pid, r.rip - 1) == 0xCB) {
                unsigned long addr = 0;
                if (sp > 0) addr = call_stack[--sp];
                print_leave_desc(t->pid, addr);
            }
            prev = r;
            prev_valid = 1;
            if (sig != SIGTRAP)
                print_signal(sig);
            ptrace(PTRACE_SINGLESTEP, t->pid, 0, 0);
            continue;
        }
    }
    return 0;
}

int run_trace(traced_t *t)
{
    pid_t pid = fork();
    if (pid == 0) {
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        kill(getpid(), SIGSTOP);
        execvp(t->prog, t->argv);
        _exit(1);
    } else if (pid > 0) {
        t->pid = pid;
        t->main_addr = elf_find_symbol_addr(t->prog, "main");
        print_enter_main(t);
        waitpid(pid, NULL, 0);
        return trace_loop(t);
    }
    return -1;
}

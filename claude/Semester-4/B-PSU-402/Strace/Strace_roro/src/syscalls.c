/*
** EPITECH PROJECT, 2025
** Strace
** File description:
** System call names and information
*/

#include "strace.h"

static syscall_info_t syscalls[] = {
    {__NR_read, "read", 3},
    {__NR_write, "write", 3},
    {__NR_open, "open", 3},
    {__NR_close, "close", 1},
    {__NR_stat, "stat", 2},
    {__NR_fstat, "fstat", 2},
    {__NR_lstat, "lstat", 2},
    {__NR_poll, "poll", 3},
    {__NR_lseek, "lseek", 3},
    {__NR_mmap, "mmap", 6},
    {__NR_mprotect, "mprotect", 3},
    {__NR_munmap, "munmap", 2},
    {__NR_brk, "brk", 1},
    {__NR_rt_sigaction, "rt_sigaction", 4},
    {__NR_rt_sigprocmask, "rt_sigprocmask", 4},
    {__NR_rt_sigreturn, "rt_sigreturn", 0},
    {__NR_ioctl, "ioctl", 3},
    {__NR_pread64, "pread64", 4},
    {__NR_pwrite64, "pwrite64", 4},
    {__NR_readv, "readv", 3},
    {__NR_writev, "writev", 3},
    {__NR_access, "access", 2},
    {__NR_pipe, "pipe", 1},
    {__NR_select, "select", 5},
    {__NR_sched_yield, "sched_yield", 0},
    {__NR_mremap, "mremap", 5},
    {__NR_msync, "msync", 3},
    {__NR_mincore, "mincore", 3},
    {__NR_madvise, "madvise", 3},
    {__NR_shmget, "shmget", 3},
    {__NR_shmat, "shmat", 3},
    {__NR_shmctl, "shmctl", 3},
    {__NR_dup, "dup", 1},
    {__NR_dup2, "dup2", 2},
    {__NR_pause, "pause", 0},
    {__NR_nanosleep, "nanosleep", 2},
    {__NR_getitimer, "getitimer", 2},
    {__NR_alarm, "alarm", 1},
    {__NR_setitimer, "setitimer", 3},
    {__NR_getpid, "getpid", 0},
    {__NR_sendfile, "sendfile", 4},
    {__NR_socket, "socket", 3},
    {__NR_connect, "connect", 3},
    {__NR_accept, "accept", 3},
    {__NR_sendto, "sendto", 6},
    {__NR_recvfrom, "recvfrom", 6},
    {__NR_sendmsg, "sendmsg", 3},
    {__NR_recvmsg, "recvmsg", 3},
    {__NR_shutdown, "shutdown", 2},
    {__NR_bind, "bind", 3},
    {__NR_listen, "listen", 2},
    {__NR_getsockname, "getsockname", 3},
    {__NR_getpeername, "getpeername", 3},
    {__NR_socketpair, "socketpair", 4},
    {__NR_setsockopt, "setsockopt", 5},
    {__NR_getsockopt, "getsockopt", 5},
    {__NR_clone, "clone", 5},
    {__NR_fork, "fork", 0},
    {__NR_vfork, "vfork", 0},
    {__NR_execve, "execve", 3},
    {__NR_exit, "exit", 1},
    {__NR_wait4, "wait4", 4},
    {__NR_kill, "kill", 2},
    {__NR_uname, "uname", 1},
    {__NR_semget, "semget", 3},
    {__NR_semop, "semop", 3},
    {__NR_semctl, "semctl", 4},
    {__NR_shmdt, "shmdt", 1},
    {__NR_msgget, "msgget", 2},
    {__NR_msgsnd, "msgsnd", 4},
    {__NR_msgrcv, "msgrcv", 5},
    {__NR_msgctl, "msgctl", 3},
    {__NR_fcntl, "fcntl", 3},
    {__NR_flock, "flock", 2},
    {__NR_fsync, "fsync", 1},
    {__NR_fdatasync, "fdatasync", 1},
    {__NR_truncate, "truncate", 2},
    {__NR_ftruncate, "ftruncate", 2},
    {__NR_getdents, "getdents", 3},
    {__NR_getcwd, "getcwd", 2},
    {__NR_chdir, "chdir", 1},
    {__NR_fchdir, "fchdir", 1},
    {__NR_rename, "rename", 2},
    {__NR_mkdir, "mkdir", 2},
    {__NR_rmdir, "rmdir", 1},
    {__NR_creat, "creat", 2},
    {__NR_link, "link", 2},
    {__NR_unlink, "unlink", 1},
    {__NR_symlink, "symlink", 2},
    {__NR_readlink, "readlink", 3},
    {__NR_chmod, "chmod", 2},
    {__NR_fchmod, "fchmod", 2},
    {__NR_chown, "chown", 3},
    {__NR_fchown, "fchown", 3},
    {__NR_lchown, "lchown", 3},
    {__NR_umask, "umask", 1},
    {__NR_gettimeofday, "gettimeofday", 2},
    {__NR_getrlimit, "getrlimit", 2},
    {__NR_getrusage, "getrusage", 2},
    {__NR_sysinfo, "sysinfo", 1},
    {__NR_times, "times", 1},
    {__NR_ptrace, "ptrace", 4},
    {__NR_getuid, "getuid", 0},
    {__NR_syslog, "syslog", 3},
    {__NR_getgid, "getgid", 0},
    {__NR_setuid, "setuid", 1},
    {__NR_setgid, "setgid", 1},
    {__NR_geteuid, "geteuid", 0},
    {__NR_getegid, "getegid", 0},
    {__NR_setpgid, "setpgid", 2},
    {__NR_getppid, "getppid", 0},
    {__NR_getpgrp, "getpgrp", 0},
    {__NR_setsid, "setsid", 0},
    {__NR_setreuid, "setreuid", 2},
    {__NR_setregid, "setregid", 2},
    {__NR_getgroups, "getgroups", 2},
    {__NR_setgroups, "setgroups", 2},
    {__NR_setresuid, "setresuid", 3},
    {__NR_getresuid, "getresuid", 3},
    {__NR_setresgid, "setresgid", 3},
    {__NR_getresgid, "getresgid", 3},
    {__NR_getpgid, "getpgid", 1},
    {__NR_setfsuid, "setfsuid", 1},
    {__NR_setfsgid, "setfsgid", 1},
    {__NR_getsid, "getsid", 1},
    {__NR_capget, "capget", 2},
    {__NR_capset, "capset", 2},
    {-1, NULL, 0}
};

const char *get_syscall_name(long syscall_num)
{
    int i = 0;

    while (syscalls[i].name != NULL) {
        if (syscalls[i].number == syscall_num)
            return syscalls[i].name;
        i++;
    }
    return "unknown";
}

static int get_syscall_nb_args(long syscall_num)
{
    int i = 0;

    while (syscalls[i].name != NULL) {
        if (syscalls[i].number == syscall_num)
            return syscalls[i].nb_args;
        i++;
    }
    return 0;
}

void print_hex_args(long *args, int nb_args)
{
    int i = 0;

    for (i = 0; i < nb_args; i++) {
        printf("0x%lx", args[i]);
        if (i < nb_args - 1)
            printf(", ");
    }
}

void print_detailed_args(long syscall_num, long *args)
{
    const char *name = get_syscall_name(syscall_num);

    if (strcmp(name, "write") == 0 || strcmp(name, "read") == 0) {
        printf("%ld, 0x%lx, %ld", args[0], args[1], args[2]);
    } else if (strcmp(name, "open") == 0) {
        printf("0x%lx, %ld, %ld", args[0], args[1], args[2]);
    } else if (strcmp(name, "close") == 0) {
        printf("%ld", args[0]);
    } else if (strcmp(name, "mmap") == 0) {
        printf("0x%lx, %ld, %ld, %ld, %ld, %ld", 
               args[0], args[1], args[2], args[3], args[4], args[5]);
    } else {
        int nb_args = get_syscall_nb_args(syscall_num);
        print_hex_args(args, nb_args);
    }
}

void print_syscall(long syscall_num, long *args, long ret, int detailed)
{
    const char *name = get_syscall_name(syscall_num);
    int nb_args = get_syscall_nb_args(syscall_num);

    printf("%s(", name);
    if (detailed) {
        print_detailed_args(syscall_num, args);
    } else {
        print_hex_args(args, nb_args);
    }
    printf(") = ");
    if (ret == -1) {
        printf("?");
    } else {
        printf("0x%lx", ret);
    }
    printf("\n");
}
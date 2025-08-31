/*
** EPITECH PROJECT, 2025
** Strace_roro
** File description:
** syscall table (x86_64 Linux subset)
*/

#include "strace.h"

static const call_t syscalls[] = {
    [0] = {"read", 3, {ARG_INT, ARG_PTR, ARG_INT}},
    [1] = {"write", 3, {ARG_INT, ARG_PTR, ARG_INT}},
    [2] = {"open", 3, {ARG_STR, ARG_INT, ARG_INT}},
    [3] = {"close", 1, {ARG_INT}},
    [4] = {"stat", 2, {ARG_STR, ARG_PTR}},
    [5] = {"fstat", 2, {ARG_INT, ARG_PTR}},
    [6] = {"lstat", 2, {ARG_STR, ARG_PTR}},
    [9] = {"mmap", 6, {ARG_PTR, ARG_INT, ARG_INT, ARG_INT, ARG_INT, ARG_INT}},
    [10] = {"mprotect", 3, {ARG_PTR, ARG_INT, ARG_INT}},
    [11] = {"munmap", 2, {ARG_PTR, ARG_INT}},
    [12] = {"brk", 1, {ARG_PTR}},
    [21] = {"access", 2, {ARG_STR, ARG_INT}},
    [59] = {"execve", 3, {ARG_STR, ARG_PTR, ARG_PTR}},
    [60] = {"exit", 1, {ARG_INT}},
    [62] = {"kill", 2, {ARG_INT, ARG_INT}},
    [63] = {"uname", 1, {ARG_PTR}},
    [72] = {"fcntl", 3, {ARG_INT, ARG_INT, ARG_PTR}},
    [79] = {"getcwd", 2, {ARG_PTR, ARG_INT}},
    [80] = {"chdir", 1, {ARG_STR}},
    [85] = {"creat", 2, {ARG_STR, ARG_INT}},
    [87] = {"unlink", 1, {ARG_STR}},
    [89] = {"readlink", 3, {ARG_STR, ARG_PTR, ARG_INT}},
    [202] = {"futex", 6, {ARG_PTR, ARG_INT, ARG_INT, ARG_PTR, ARG_PTR, ARG_INT}},
    [217] = {"getdents64", 3, {ARG_INT, ARG_PTR, ARG_INT}},
    [231] = {"exit_group", 1, {ARG_INT}},
    [257] = {"openat", 4, {ARG_INT, ARG_STR, ARG_INT, ARG_INT}},
    [262] = {"newfstatat", 4, {ARG_INT, ARG_STR, ARG_PTR, ARG_INT}},
    [263] = {"unlinkat", 3, {ARG_INT, ARG_STR, ARG_INT}},
    [268] = {"readlinkat", 4, {ARG_INT, ARG_STR, ARG_PTR, ARG_INT}},
};

const call_t *sys_get(long id)
{
    if (id < 0)
        return 0;
    if ((size_t)id >= (sizeof(syscalls) / sizeof(syscalls[0])))
        return 0;
    return &syscalls[id];
}

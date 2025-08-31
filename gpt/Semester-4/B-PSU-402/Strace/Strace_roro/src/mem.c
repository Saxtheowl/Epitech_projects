/*
** EPITECH PROJECT, 2025
** Strace_roro
** File description:
** mem read
*/

#include <sys/ptrace.h>
#include <string.h>
#include "strace.h"

int read_string(pid_t pid, unsigned long addr, char *buf, size_t max)
{
    size_t i;
    union { long val; char bytes[sizeof(long)]; } u;

    if (addr == 0) {
        buf[0] = '\0';
        return 0;
    }
    for (i = 0; i + sizeof(long) <= max; i += sizeof(long)) {
        errno = 0;
        u.val = ptrace(PTRACE_PEEKDATA, pid, (void *)(addr + i), 0);
        if (errno)
            break;
        memcpy(buf + i, u.bytes, sizeof(long));
        if (memchr(u.bytes, '\0', sizeof(long)))
            return 0;
    }
    buf[max - 1] = '\0';
    return 0;
}


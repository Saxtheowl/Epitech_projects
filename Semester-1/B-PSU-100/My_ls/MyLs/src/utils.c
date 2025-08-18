/*
** EPITECH PROJECT, 2025
** my_ls
** File description:
** Small utility helpers (string, memory, output).
*/
#include "my_ls.h"
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

size_t my_strlen(const char *s)
{
    size_t n = 0;
    if (!s) return 0;
    while (s[n] != '\0') n++;
    return n;
}

int my_strcmp(const char *a, const char *b)
{
    size_t i = 0;
    if (a == b) return 0;
    if (!a) return -1;
    if (!b) return 1;
    while (a[i] && b[i]) {
        if ((unsigned char)a[i] != (unsigned char)b[i])
            return (int)((unsigned char)a[i] - (unsigned char)b[i]);
        ++i;
    }
    if (a[i]) return 1;
    if (b[i]) return -1;
    return 0;
}

char *my_strdup(const char *s)
{
    size_t n = my_strlen(s);
    char *p = (char *)xmalloc(n + 1);
    for (size_t i = 0; i < n; ++i) p[i] = s[i];
    p[n] = '\0';
    return p;
}

void *xmalloc(size_t n)
{
    void *p = malloc(n);
    if (!p) {
        my_putstr_fd(2, "my_ls: memory allocation failed\n");
        exit(84);
    }
    return p;
}

void my_putstr_fd(int fd, const char *s)
{
    if (!s) return;
    write(fd, s, my_strlen(s));
}

void my_putnbr_fd(int fd, long n)
{
    char buf[32];
    int i = 0;
    long x = n;
    if (n == 0) {
        write(fd, "0", 1);
        return;
    }
    if (n < 0) {
        write(fd, "-", 1);
        x = -n;
    }
    while (x > 0 && i < (int)sizeof(buf)) {
        buf[i++] = (char)('0' + (x % 10));
        x /= 10;
    }
    for (int j = i - 1; j >= 0; --j) write(fd, &buf[j], 1);
}

void my_perror_path(const char *prefix, const char *path, int errnum)
{
    my_putstr_fd(2, prefix);
    my_putstr_fd(2, ": ");
    my_putstr_fd(2, path);
    my_putstr_fd(2, ": ");
    my_putstr_fd(2, strerror(errnum));
    my_putstr_fd(2, "\n");
}

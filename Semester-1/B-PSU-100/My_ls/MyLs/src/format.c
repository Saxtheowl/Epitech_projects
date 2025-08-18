/*
** EPITECH PROJECT, 2025
** my_ls
** File description:
** Formatting helpers for -l output.
*/
#include "my_ls.h"
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

void format_mode(mode_t mode, char *dst)
{
    dst[0] = S_ISDIR(mode) ? 'd' :
             S_ISLNK(mode) ? 'l' :
             S_ISCHR(mode) ? 'c' :
             S_ISBLK(mode) ? 'b' :
             S_ISSOCK(mode) ? 's' :
             S_ISFIFO(mode) ? 'p' : '-';
    const char *rwx = "rwx";
    for (int i = 0; i < 9; ++i) {
        dst[1 + i] = (mode & (1 << (8 - i))) ? rwx[i % 3] : '-';
    }
    /* setuid/setgid/sticky bits adjustments */
    if (mode & S_ISUID) dst[3] = (dst[3] == 'x') ? 's' : 'S';
    if (mode & S_ISGID) dst[6] = (dst[6] == 'x') ? 's' : 'S';
    if (mode & S_ISVTX) dst[9] = (dst[9] == 'x') ? 't' : 'T';
    dst[10] = '\0';
}

void format_time(time_t t, char *dst)
{
    /* Use ctime format and slice: "Mmm dd HH:MM" */
    const char *s = ctime(&t);
    /* ctime returns 26 chars: "Www Mmm dd HH:MM:SS YYYY\n\0" */
    for (int i = 0; i < 12; ++i) dst[i] = s[4 + i];
    dst[12] = '\0';
}

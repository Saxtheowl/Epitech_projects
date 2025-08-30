/*
** EPITECH PROJECT, 2025
** MyLs_roro
** File description:
** Format long listing
*/

#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>
#include "my_ls.h"

static void mode_to_str(mode_t m, char out[11])
{
    out[0] = S_ISDIR(m) ? 'd' : S_ISLNK(m) ? 'l' : '-';
    out[1] = (m & S_IRUSR) ? 'r' : '-';
    out[2] = (m & S_IWUSR) ? 'w' : '-';
    out[3] = (m & S_IXUSR) ? 'x' : '-';
    out[4] = (m & S_IRGRP) ? 'r' : '-';
    out[5] = (m & S_IWGRP) ? 'w' : '-';
    out[6] = (m & S_IXGRP) ? 'x' : '-';
    out[7] = (m & S_IROTH) ? 'r' : '-';
    out[8] = (m & S_IWOTH) ? 'w' : '-';
    out[9] = (m & S_IXOTH) ? 'x' : '-';
    out[10] = '\0';
}

static void time_str(time_t t, char *buf, size_t n)
{
    struct tm *tm;

    tm = localtime(&t);
    strftime(buf, n, "%b %e %H:%M", tm);
}

void print_long(const entry_t *e)
{
    char modes[11];
    struct passwd *pw;
    struct group *gr;
    char tb[64];

    mode_to_str(e->st.st_mode, modes);
    pw = getpwuid(e->st.st_uid);
    gr = getgrgid(e->st.st_gid);
    time_str(e->st.st_mtime, tb, sizeof(tb));
    printf("%s %lu %s %s %ld %s %s\n",
        modes,
        (unsigned long)e->st.st_nlink,
        pw ? pw->pw_name : "?",
        gr ? gr->gr_name : "?",
        (long)e->st.st_size,
        tb,
        e->name);
}

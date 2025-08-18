/*
** EPITECH PROJECT, 2025
** my_ls
** File description:
** Printing entries with or without -l.
*/
#include "my_ls.h"
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>

void print_name(const entry_t *e)
{
    my_putstr_fd(1, e->name);
}

void print_long(const entry_t *e)
{
    char mode[11];
    char tbuf[16];
    struct passwd *pw = getpwuid(e->st.st_uid);
    struct group *gr = getgrgid(e->st.st_gid);

    format_mode(e->st.st_mode, mode);
    format_time(e->st.st_mtime, tbuf);

    my_putstr_fd(1, mode);
    my_putstr_fd(1, " ");
    my_putnbr_fd(1, (long)e->st.st_nlink);
    my_putstr_fd(1, " ");
    my_putstr_fd(1, pw ? pw->pw_name : "?");
    my_putstr_fd(1, " ");
    my_putstr_fd(1, gr ? gr->gr_name : "?");
    my_putstr_fd(1, " ");
    my_putnbr_fd(1, (long)e->st.st_size);
    my_putstr_fd(1, " ");
    my_putstr_fd(1, tbuf);
    my_putstr_fd(1, " ");
    my_putstr_fd(1, e->name);
    if (e->is_link) {
        my_putstr_fd(1, " -> ");
        my_putstr_fd(1, e->link_target);
    }
}

void print_entries(entry_t *arr, size_t n, const options_t *opts, const char *header)
{
    (void)header;
    for (size_t i = 0; i < n; ++i) {
        if (opts->opt_l) {
            print_long(&arr[i]);
        } else {
            print_name(&arr[i]);
        }
        my_putstr_fd(1, "\n");
    }
}

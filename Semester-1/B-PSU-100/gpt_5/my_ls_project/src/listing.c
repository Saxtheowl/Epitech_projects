/*
** EPITECH PROJECT, 2025
** MY_LS
** File description:
** Epitech-style source file for my_ls project
*/
#include "my_ls.h"
#include <stdlib.h>
#include <unistd.h>

static void print_time(time_t t)
{
    char *s = ctime(&t);
    size_t i = 4;
    size_t end = 16;

    if (!s) {
        my_write_str(1, "??? ?? ??:?? ");
        return;
    }
    while (i < end && s[i] != '\0') {
        my_write_char(1, s[i]);
        i++;
    }
    my_write_char(1, ' ');
}

static void print_name(entry_t *e)
{
    my_write_str(1, e->name);
    if (e->is_link && e->link_len > 0) {
        my_write_str(1, " -> ");
        my_write_str(1, e->link_target);
    }
    my_write_char(1, '\n');
}

void compute_widths(entry_t *arr, size_t n, widths_t *w)
{
    size_t i = 0;
    size_t tmp;
    struct passwd *pw;
    struct group *gr;

    w->lnk_w = 0;
    w->usr_w = 0;
    w->grp_w = 0;
    w->size_w = 0;
    w->total_blocks = 0;
    while (i < n) {
        long long blks = (long long)arr[i].st.st_blocks / 2;

        w->total_blocks += blks;
        tmp = 1;
        for (size_t v = arr[i].st.st_nlink; v >= 10; v /= 10)
            tmp++;
        if (tmp > w->lnk_w)
            w->lnk_w = tmp;
        pw = getpwuid(arr[i].st.st_uid);
        if (pw) {
            tmp = my_strlen(pw->pw_name);
        } else {
            tmp = 1;
            for (size_t v = arr[i].st.st_uid; v >= 10; v /= 10)
                tmp++;
        }
        if (tmp > w->usr_w)
            w->usr_w = tmp;
        gr = getgrgid(arr[i].st.st_gid);
        if (gr) {
            tmp = my_strlen(gr->gr_name);
        } else {
            tmp = 1;
            for (size_t v = arr[i].st.st_gid; v >= 10; v /= 10)
                tmp++;
        }
        if (tmp > w->grp_w)
            w->grp_w = tmp;
        tmp = 1;
        for (size_t v = (size_t)arr[i].st.st_size; v >= 10; v /= 10)
            tmp++;
        if (tmp > w->size_w)
            w->size_w = tmp;
        i++;
    }
}

void print_long_entry(entry_t *e, widths_t *w)
{
    char perm[11];
    struct passwd *pw;
    struct group *gr;
    size_t pad;

    build_perm_string(e->st.st_mode, perm);
    my_write_str(1, perm);
    my_write_char(1, ' ');

    pad = w->lnk_w;
    for (size_t v = e->st.st_nlink; v >= 10; v /= 10)
        pad--;
    while (pad-- > 1)
        my_write_char(1, ' ');
    my_write_ll(1, (long long)e->st.st_nlink);
    my_write_char(1, ' ');

    pw = getpwuid(e->st.st_uid);
    if (pw) {
        size_t ulen = my_strlen(pw->pw_name);

        my_write_str(1, pw->pw_name);
        while (ulen++ < w->usr_w)
            my_write_char(1, ' ');
    } else {
        my_write_ll(1, (long long)e->st.st_uid);
        pad = w->usr_w;
        for (size_t v = e->st.st_uid; v >= 10; v /= 10)
            pad--;
        while (pad-- > 0)
            my_write_char(1, ' ');
    }
    my_write_char(1, ' ');

    gr = getgrgid(e->st.st_gid);
    if (gr) {
        size_t glen = my_strlen(gr->gr_name);

        my_write_str(1, gr->gr_name);
        while (glen++ < w->grp_w)
            my_write_char(1, ' ');
    } else {
        my_write_ll(1, (long long)e->st.st_gid);
        pad = w->grp_w;
        for (size_t v = e->st.st_gid; v >= 10; v /= 10)
            pad--;
        while (pad-- > 0)
            my_write_char(1, ' ');
    }
    my_write_char(1, ' ');

    pad = w->size_w;
    for (size_t v = (size_t)e->st.st_size; v >= 10; v /= 10)
        pad--;
    while (pad-- > 1)
        my_write_char(1, ' ');
    my_write_ll(1, (long long)e->st.st_size);
    my_write_char(1, ' ');

    print_time(e->st.st_mtime);
    print_name(e);
}

static void print_entries(entry_t *arr, size_t n, options_t *opts)
{
    size_t i = 0;
    widths_t w;

    if (opts->l_opt) {
        compute_widths(arr, n, &w);
        my_write_str(1, "total ");
        my_write_ll(1, w.total_blocks);
        my_write_char(1, '\n');
        while (i < n) {
            print_long_entry(&arr[i], &w);
            i++;
        }
    } else {
        while (i < n) {
            my_write_str(1, arr[i].name);
            my_write_char(1, '\n');
            i++;
        }
    }
}

static int is_dotdot(const char *name)
{
    return (name[0] == '.' && (name[1] == '\0' ||
            (name[1] == '.' && name[2] == '\0')));
}

static int list_dir(const char *path, options_t *opts, int header)
{
    entry_t *arr = NULL;
    size_t n = 0;
    size_t i = 0;
    int ret;

    ret = read_entries(path, opts, &arr, &n);
    if (ret < 0)
        return -1;
    sort_entries(arr, n, opts->t_opt, opts->r_opt);
    if (header)
        my_write_str(1, path), my_write_str(1, ":
");
    print_entries(arr, n, opts);
    if (opts->R_opt) {
        while (i < n) {
            if (S_ISDIR(arr[i].st.st_mode) && !is_dotdot(arr[i].name)) {
                my_write_char(1, '\n');
                my_ls_single_path(arr[i].path, opts, 1);
            }
            i++;
        }
    }
    free_entries(arr, n);
    return 0;
}

static int print_file(const char *path, const char *name, options_t *opts)
{
    entry_t e;
    widths_t w;

    e.name = (char *)name;
    e.path = (char *)path;
    if (lstat(path, &e.st) < 0)
        return -1;
    e.is_link = 0;
    e.link_len = 0;
    e.link_target[0] = '\0';
    if (S_ISLNK(e.st.st_mode)) {
        e.is_link = 1;
        e.link_len = readlink(path, e.link_target,
            sizeof(e.link_target) - 1);
        if (e.link_len >= 0)
            e.link_target[e.link_len] = '\0';
    }
    if (opts->l_opt) {
        w.lnk_w = 1;
        w.usr_w = 0;
        w.grp_w = 0;
        w.size_w = 1;
        w.total_blocks = 0;
        print_long_entry(&e, &w);
    } else {
        my_write_str(1, name);
        my_write_char(1, '\n');
    }
    return 0;
}

int my_ls_single_path(const char *path, options_t *opts, int show_header)
{
    struct stat st;

    if (lstat(path, &st) < 0)
        return -1;
    if (opts->d_opt || !S_ISDIR(st.st_mode))
        return print_file(path, path, opts);
    return list_dir(path, opts, show_header);
}

int my_ls_paths(int argc, char **argv, int from, options_t *opts)
{
    int i = from;
    int many = (argc - from) > 1;
    int ret;

    if (from >= argc)
        return list_dir(".", opts, 0);
    while (i < argc) {
        ret = my_ls_single_path(argv[i], opts, many);
        if (ret < 0)
            return -1;
        if (i + 1 < argc)
            my_write_char(1, '\n');
        i++;
    }
    return 0;
}

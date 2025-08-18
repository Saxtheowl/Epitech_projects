/*
** EPITECH PROJECT, 2025
** my_ls
** File description:
** Directory listing (non-recursive & recursive -R).
*/
#include "my_ls.h"
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

static int push_entry(vec_t *v, const entry_t *e)
{
    if (v->size == v->cap) {
        size_t ncap = v->cap ? v->cap * 2 : 16;
        entry_t *nd = (entry_t *)realloc(v->data, ncap * sizeof(entry_t));
        if (!nd) return -1;
        v->data = nd;
        v->cap = ncap;
    }
    v->data[v->size++] = *e;
    return 0;
}

static void free_vec(vec_t *v)
{
    if (!v) return;
    for (size_t i = 0; i < v->size; ++i) {
        free(v->data[i].name);
        free(v->data[i].fullpath);
    }
    free(v->data);
}

static int read_dir_collect(const char *path, const options_t *opts, vec_t *out, long *total_blocks)
{
    DIR *d = opendir(path);
    if (!d) {
        my_perror_path("my_ls", path, errno);
        return -1;
    }
    struct dirent *de;
    char buf[PATHBUF_SIZE];
    while ((de = readdir(d)) != NULL) {
        const char *name = de->d_name;
        if (!opts->opt_a && name[0] == '.' ) continue;
        entry_t e;
        memset(&e, 0, sizeof(e));
        e.name = my_strdup(name);
        if (join_path(buf, sizeof(buf), path, name) != 0) {
            my_perror_path("my_ls", path, ENAMETOOLONG);
            closedir(d);
            return -1;
        }
        e.fullpath = my_strdup(buf);
        if (lstat(e.fullpath, &e.st) == -1) {
            e.stat_ok = false;
            my_perror_path("my_ls", e.fullpath, errno);
        } else {
            e.stat_ok = true;
            if (S_ISLNK(e.st.st_mode)) {
                ssize_t r = readlink(e.fullpath, e.link_target, sizeof(e.link_target)-1);
                if (r >= 0) { e.link_target[r] = '\0'; e.is_link = true; }
            }
            if (total_blocks) *total_blocks += (long)e.st.st_blocks;
        }
        if (push_entry(out, &e) != 0) {
            closedir(d);
            return -1;
        }
    }
    closedir(d);
    return 0;
}

int list_directory(const char *path, const options_t *opts, bool print_header)
{
    vec_t v = {0};
    long total_blocks = 0;
    int status = 0;

    if (opts->opt_d) {
        entry_t e;
        memset(&e, 0, sizeof(e));
        e.name = my_strdup(path);
        e.fullpath = my_strdup(path);
        if (lstat(path, &e.st) == -1) {
            my_perror_path("my_ls", path, errno);
            free(e.name); free(e.fullpath);
            return -1;
        }
        entry_t one[1] = { e };
        sort_entries(one, 1, opts->opt_t, opts->opt_r);
        print_entries(one, 1, opts, NULL);
        free(e.name); free(e.fullpath);
        return 0;
    }

    if (read_dir_collect(path, opts, &v, opts->opt_l ? &total_blocks : NULL) != 0) {
        free_vec(&v);
        return -1;
    }
    sort_entries(v.data, v.size, opts->opt_t, opts->opt_r);

    if (print_header) {
        my_putstr_fd(1, path);
        my_putstr_fd(1, ":
");
    }
    if (opts->opt_l) {
        my_putstr_fd(1, "total ");
        my_putnbr_fd(1, total_blocks / 2); /* GNU ls shows 1K blocks by default; st_blocks usually 512B */
        my_putstr_fd(1, "\n");
    }
    print_entries(v.data, v.size, opts, NULL);

    if (opts->opt_R) {
        for (size_t i = 0; i < v.size; ++i) {
            if (!v.data[i].stat_ok) continue;
            if (S_ISDIR(v.data[i].st.st_mode)) {
                const char *name = v.data[i].name;
                if (my_strcmp(name, ".") == 0 || my_strcmp(name, "..") == 0) continue;
                my_putstr_fd(1, "\n");
                list_directory(v.data[i].fullpath, opts, true);
            }
        }
    }

    free_vec(&v);
    return status;
}

#define _XOPEN_SOURCE 700
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../include/my_ls.h"

static void free_entry(entry_t *e)
{
    if (!e)
        return;
    free(e->name);
    free(e->path);
    e->name = NULL;
    e->path = NULL;
}

int stat_entry(const char *dir, const char *name, entry_t *out)
{
    size_t dlen = strlen(dir);
    size_t need_slash = (dlen > 0 && dir[dlen - 1] != '/') ? 1u : 0u;
    size_t nlen = strlen(name);
    size_t plen = dlen + need_slash + nlen + 1;

    char *path = malloc(plen);
    if (!path)
        return -1;
    char *dst = path;
    if (dlen > 0) {
        memcpy(dst, dir, dlen);
        dst += dlen;
        if (need_slash)
            *dst++ = '/';
    }
    memcpy(dst, name, nlen + 1);

    char *name_copy = strdup(name);
    if (!name_copy) {
        free(path);
        return -1;
    }

    struct stat st;
    if (lstat(path, &st) < 0) {
        free(name_copy);
        free(path);
        return -1;
    }

    out->name = name_copy;
    out->path = path;
    out->st = st;
    return 0;
}

static int is_hidden(const char *name) { return name[0] == '.'; }

int list_directory(const char *path, const ls_opts_t *opts, int print_header)
{
    DIR *d = opendir(path);
    if (!d) {
        fprintf(stderr, "my_ls: %s: %s\n", path, strerror(errno));
        return 84;
    }
    if (print_header)
        printf("%s:\n", path);

    size_t cap = 0;
    size_t n = 0;
    entry_t *arr = NULL;
    struct dirent *de;
    while ((de = readdir(d))) {
        if (!opts->opt_a && is_hidden(de->d_name)) continue;
        if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) {
            if (!(opts->opt_a)) continue;
        }
        entry_t e;
        if (stat_entry(path, de->d_name, &e) != 0)
            continue;
        if (n == cap) {
            size_t new_cap = cap ? cap * 2 : 32;
            entry_t *tmp = realloc(arr, new_cap * sizeof(*tmp));
            if (!tmp) {
                free_entry(&e);
                free_entries(arr, (int)n);
                closedir(d);
                return 84;
            }
            arr = tmp;
            cap = new_cap;
        }
        arr[n++] = e;
    }
    closedir(d);
    sort_entries(arr, (int)n, opts);
    print_entries(path, arr, (int)n, opts);

    if (opts->opt_R) {
        for (size_t i = 0; i < n; ++i) {
            if (S_ISDIR(arr[i].st.st_mode)) {
                if (strcmp(arr[i].name, ".") == 0 || strcmp(arr[i].name, "..") == 0) continue;
                printf("\n");
                list_directory(arr[i].path, opts, 1);
            }
        }
    }

    free_entries(arr, (int)n);
    return 0;
}

int list_paths(char **paths, int npaths, const ls_opts_t *opts)
{
    int ret = 0;
    entry_t *files = NULL; int nf = 0; int cf = 0;
    entry_t *dirs = NULL; int nd = 0; int cd = 0;
    for (int i = 0; i < npaths; ++i) {
        struct stat st;
        if (lstat(paths[i], &st) < 0) {
            fprintf(stderr, "my_ls: %s: %s\n", paths[i], strerror(errno));
            ret = 84; continue;
        }
        if (S_ISDIR(st.st_mode)) {
            if (nd == cd) {
                cd = cd ? cd * 2 : 8;
                entry_t *tmp = realloc(dirs, cd * sizeof(*dirs));
                if (!tmp) { ret = 84; continue; }
                dirs = tmp;
            }
            entry_t e = { strdup(paths[i]), strdup(paths[i]), st };
            if (!e.name || !e.path) {
                free(e.name);
                free(e.path);
                ret = 84;
                continue;
            }
            dirs[nd++] = e;
        } else {
            if (nf == cf) {
                cf = cf ? cf * 2 : 8;
                entry_t *tmp = realloc(files, cf * sizeof(*files));
                if (!tmp) { ret = 84; continue; }
                files = tmp;
            }
            entry_t e = { strdup(paths[i]), strdup(paths[i]), st };
            if (!e.name || !e.path) {
                free(e.name);
                free(e.path);
                ret = 84;
                continue;
            }
            files[nf++] = e;
        }
    }
    if (nf > 0) {
        sort_entries(files, nf, opts);
        print_entries(NULL, files, nf, opts);
        if (nd > 0) printf("\n");
    }
    for (int i = 0; i < nd; ++i) {
        list_directory(dirs[i].path, opts, (npaths > 1));
        if (i+1 < nd) printf("\n");
    }
    free_entries(files, nf); free_entries(dirs, nd);
    return ret;
}

void free_entries(entry_t *arr, int n)
{
    if (!arr) return;
    for (int i = 0; i < n; ++i) { free(arr[i].name); free(arr[i].path); }
    free(arr);
}

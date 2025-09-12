#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../include/my_ls.h"

int stat_entry(const char *dir, const char *name, entry_t *out)
{
    size_t dlen = strlen(dir), nlen = strlen(name);
    size_t plen = dlen + 1 + nlen + 1;
    char *path = malloc(plen);
    if (!path) return -1;
    strcpy(path, dir);
    if (dlen > 0 && dir[dlen-1] != '/') strcat(path, "/");
    strcat(path, name);
    memset(out, 0, sizeof(*out));
    out->name = strdup(name);
    out->path = path;
    if (!out->name || !out->path) return -1;
    if (lstat(path, &out->st) < 0) return -1;
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

    size_t cap = 64, n = 0;
    entry_t *arr = malloc(cap * sizeof(*arr));
    if (!arr) { closedir(d); return 84; }
    struct dirent *de;
    while ((de = readdir(d))) {
        if (!opts->opt_a && is_hidden(de->d_name)) continue;
        if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) {
            if (!(opts->opt_a)) continue;
        }
        entry_t e;
        if (stat_entry(path, de->d_name, &e) == 0) {
            if (n == cap) { cap *= 2; entry_t *na = realloc(arr, cap*sizeof(*na)); if (!na){free(arr); closedir(d); return 84;} arr = na; }
            arr[n++] = e;
        }
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
    // first, stat paths and separate files/dirs
    entry_t *files = NULL; int nf = 0; int cf = 0;
    entry_t *dirs = NULL; int nd = 0; int cd = 0;
    for (int i = 0; i < npaths; ++i) {
        struct stat st;
        if (lstat(paths[i], &st) < 0) {
            fprintf(stderr, "my_ls: %s: %s\n", paths[i], strerror(errno));
            ret = 84; continue;
        }
        if (S_ISDIR(st.st_mode)) {
            if (nd == cd) { cd = cd? cd*2: 8; dirs = realloc(dirs, cd*sizeof(*dirs)); }
            entry_t e = { strdup(paths[i]), strdup(paths[i]), st };
            dirs[nd++] = e;
        } else {
            if (nf == cf) { cf = cf? cf*2: 8; files = realloc(files, cf*sizeof(*files)); }
            entry_t e = { strdup(paths[i]), strdup(paths[i]), st };
            files[nf++] = e;
        }
    }
    // print files first
    if (nf > 0) {
        sort_entries(files, nf, opts);
        print_entries(NULL, files, nf, opts);
        if (nd > 0) printf("\n");
    }
    // print dirs
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


#ifndef MY_LS_H
#define MY_LS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

typedef struct {
    int opt_a;   // include hidden
    int opt_l;   // long format
    int opt_R;   // recursive
    int opt_t;   // sort by mtime desc
} ls_opts_t;

typedef struct {
    char *name;
    char *path;        // full path
    struct stat st;
} entry_t;

int run_ls(int argc, char **argv);
int list_paths(char **paths, int npaths, const ls_opts_t *opts);
int list_directory(const char *path, const ls_opts_t *opts, int print_header);
int stat_entry(const char *dir, const char *name, entry_t *out);
void sort_entries(entry_t *arr, int n, const ls_opts_t *opts);
void free_entries(entry_t *arr, int n);
void print_entries(const char *dir, entry_t *arr, int n, const ls_opts_t *opts);
void print_long(const entry_t *e);

#endif


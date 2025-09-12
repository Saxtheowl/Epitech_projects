#include <string.h>
#include <time.h>
#include "../include/my_ls.h"

static int cmp_name(const entry_t *a, const entry_t *b)
{
    return strcmp(a->name, b->name);
}

static int cmp_mtime(const entry_t *a, const entry_t *b)
{
    if (a->st.st_mtime == b->st.st_mtime)
        return cmp_name(a, b);
    return (a->st.st_mtime > b->st.st_mtime) ? -1 : 1; // desc
}

void sort_entries(entry_t *arr, int n, const ls_opts_t *opts)
{
    if (n <= 1) return;
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            int c = opts->opt_t ? cmp_mtime(&arr[i], &arr[j]) : cmp_name(&arr[i], &arr[j]);
            if (c > 0) { entry_t tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp; }
        }
    }
}


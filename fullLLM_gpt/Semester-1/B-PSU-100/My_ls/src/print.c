#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/stat.h>
#include "../include/my_ls.h"

static void mode_to_str(mode_t m, char *out)
{
    out[0] = S_ISDIR(m) ? 'd' : (S_ISLNK(m) ? 'l' : '-');
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

void print_long(const entry_t *e)
{
    char perm[11]; mode_to_str(e->st.st_mode, perm);
    struct passwd *pw = getpwuid(e->st.st_uid);
    struct group *gr = getgrgid(e->st.st_gid);
    char timebuf[64];
    struct tm lt; localtime_r(&e->st.st_mtime, &lt);
    strftime(timebuf, sizeof timebuf, "%b %e %H:%M", &lt);
    printf("%s %2lu %s %s %6ld %s %s\n",
        perm,
        (unsigned long)e->st.st_nlink,
        pw ? pw->pw_name : "?",
        gr ? gr->gr_name : "?",
        (long)e->st.st_size,
        timebuf,
        e->name);
}

void print_entries(const char *dir, entry_t *arr, int n, const ls_opts_t *opts)
{
    if (opts->opt_l && dir) {
        // mimic total from st_blocks/2
        long blocks = 0;
        for (int i = 0; i < n; ++i) blocks += arr[i].st.st_blocks;
        printf("total %ld\n", blocks/2);
    }
    for (int i = 0; i < n; ++i) {
        if (opts->opt_l) print_long(&arr[i]);
        else printf("%s\n", arr[i].name);
    }
}


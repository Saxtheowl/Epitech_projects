/*
** EPITECH PROJECT, 2025
** my_ls
** File description:
** Public header for my_ls implementation.
*/

#ifndef MY_LS_H_
#define MY_LS_H_

#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define PATHBUF_SIZE 4096

typedef struct options_s {
    bool opt_a;
    bool opt_l;
    bool opt_R;
    bool opt_d;
    bool opt_r;
    bool opt_t;
} options_t;

typedef struct entry_s {
    char *name;
    char *fullpath;
    struct stat st;
    bool stat_ok;
    bool is_link;
    char link_target[PATHBUF_SIZE];
} entry_t;

typedef struct vec_s {
    entry_t *data;
    size_t size;
    size_t cap;
} vec_t;

/* options.c */
int parse_options(int ac, char **av, options_t *opts, int *first_path_idx);

/* utils.c */
size_t my_strlen(const char *s);
int my_strcmp(const char *a, const char *b);
char *my_strdup(const char *s);
void *xmalloc(size_t n);
void my_perror_path(const char *prefix, const char *path, int errnum);
void my_putstr_fd(int fd, const char *s);
void my_putnbr_fd(int fd, long n);

/* path.c */
int join_path(char *out, size_t outsz, const char *a, const char *b);

/* sort.c */
void sort_entries(entry_t *arr, size_t n, bool by_time, bool reverse);

/* listing.c */
int list_paths(int ac, char **av, int first_path, const options_t *opts);

/* format.c */
void format_mode(mode_t mode, char *dst /* 11 bytes incl. NUL */);
void format_time(time_t t, char *dst /* at least 13 bytes "Mmm dd HH:MM" */);

/* print.c */
void print_entries(entry_t *arr, size_t n, const options_t *opts, const char *header);
void print_long(const entry_t *e);
void print_name(const entry_t *e);

/* recursion.c */
int list_directory(const char *path, const options_t *opts, bool print_header);

#endif /* !MY_LS_H_ */

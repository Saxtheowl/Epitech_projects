/*
** EPITECH PROJECT, 2025
** MyLs_roro
** File description:
** Prototypes for my_ls
*/

#ifndef MY_LS_H
    #define MY_LS_H

    #include <sys/types.h>
    #include <sys/stat.h>
    #include <dirent.h>

    #define ERR_CODE 84

    typedef struct flags_s {
        int a;
        int l;
        int r;
        int t;
        int d;
        int R;
    } flags_t;

    typedef struct entry_s {
        char *name;
        char *path;
        struct stat st;
    } entry_t;

    int parse_flags(int ac, char **av, int *idx, flags_t *f);
    int my_ls_path(const char *path, const flags_t *f, int print_head);

    void free_entries(entry_t *arr, int n);

#endif /* MY_LS_H */

/*
** EPITECH PROJECT, 2025
** Tree
** File description:
** tree
*/

#ifndef TREE_H_
    #define TREE_H_

    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/stat.h>
    #include <dirent.h>
    #include <string.h>

    typedef struct options_s {
        int show_all;
        int dirs_only;
        int max_depth;
        int show_full_path;
    } options_t;

    typedef struct counters_s {
        int dirs;
        int files;
    } counters_t;

    int tree_main(int argc, char **argv);
    int parse_options(int argc, char **argv, options_t *opts, char **path);
    void print_tree(char *path, options_t *opts, counters_t *counters);
    void print_tree_recursive(char *path, options_t *opts, char *prefix, 
        int depth, counters_t *counters);
    int is_hidden(char *name);
    char *join_path(char *dir, char *name);
    int my_strlen(char *str);
    int my_atoi(char *str);
    void my_strcpy(char *dest, char *src);
    char *my_strdup(char *str);

#endif /* !TREE_H_ */
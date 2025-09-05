/*
** EPITECH PROJECT, 2025
** TextCount
** File description:
** text_count
*/

#ifndef TEXT_COUNT_H_
    #define TEXT_COUNT_H_

    #include <stdlib.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <string.h>

    typedef struct char_count_s {
        char character;
        int count;
        int first_appearance;
    } char_count_t;

    typedef struct flags_s {
        int sort_by_count;
        int group_same_count;
    } flags_t;

    int text_count(int argc, char **argv);
    int parse_arguments(int argc, char **argv, flags_t *flags, char **str,
        char **searched);
    void count_characters(char *str, char *searched, char_count_t **counts,
        int *count_size);
    void print_results(char_count_t *counts, int count_size, flags_t flags);
    void sort_by_count(char_count_t *counts, int count_size);
    void sort_by_appearance(char_count_t *counts, int count_size);
    int char_in_searched(char c, char *searched);

#endif /* !TEXT_COUNT_H_ */
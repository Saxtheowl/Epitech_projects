/*
** EPITECH PROJECT, 2025
** TextCount
** File description:
** text_count
*/

#include "text_count.h"

int parse_arguments(int argc, char **argv, flags_t *flags, char **str,
    char **searched)
{
    int i = 1;

    flags->sort_by_count = 0;
    flags->group_same_count = 0;
    *searched = NULL;
    while (i < argc && argv[i][0] == '-') {
        if (strcmp(argv[i], "-r") == 0)
            flags->group_same_count = 1;
        else if (strcmp(argv[i], "-t") == 0)
            flags->sort_by_count = 1;
        else
            return 84;
        i++;
    }
    if (i >= argc)
        return 84;
    *str = argv[i];
    if (i + 1 < argc)
        *searched = argv[i + 1];
    return 0;
}

int char_in_searched(char c, char *searched)
{
    int i = 0;

    if (!searched)
        return 1;
    while (searched[i]) {
        if (searched[i] == c)
            return 1;
        i++;
    }
    return 0;
}

void count_characters(char *str, char *searched, char_count_t **counts,
    int *count_size)
{
    int i = 0;
    int j = 0;
    int found = 0;

    *count_size = 0;
    *counts = malloc(256 * sizeof(char_count_t));
    if (searched && strlen(searched) == 0)
        return;
    if (searched) {
        for (i = 0; searched[i]; i++) {
            found = 0;
            for (j = 0; j < *count_size; j++) {
                if ((*counts)[j].character == searched[i]) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                (*counts)[*count_size].character = searched[i];
                (*counts)[*count_size].count = 0;
                (*counts)[*count_size].first_appearance = 1000;
                (*count_size)++;
            }
        }
        for (i = 0; str[i]; i++) {
            for (j = 0; j < *count_size; j++) {
                if ((*counts)[j].character == str[i]) {
                    (*counts)[j].count++;
                    if ((*counts)[j].first_appearance == 1000)
                        (*counts)[j].first_appearance = i;
                    break;
                }
            }
        }
    } else {
        for (i = 0; str[i]; i++) {
            found = 0;
            for (j = 0; j < *count_size; j++) {
                if ((*counts)[j].character == str[i]) {
                    (*counts)[j].count++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                (*counts)[*count_size].character = str[i];
                (*counts)[*count_size].count = 1;
                (*counts)[*count_size].first_appearance = i;
                (*count_size)++;
            }
        }
    }
}
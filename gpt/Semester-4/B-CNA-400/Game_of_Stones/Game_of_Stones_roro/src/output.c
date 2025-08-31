/*
** EPITECH PROJECT, 2025
** Game_of_Stones
** File description:
**   Output helpers
*/

#include <stdio.h>
#include <stdlib.h>
#include "gos.h"

void print_usage(void)
{
    fprintf(stdout, "USAGE\n");
    fprintf(stdout, "./game_of_stones [--links FR P1 P2 | ");
    fprintf(stdout, "--plots FR CR n]\n");
    fprintf(stdout, "DESCRIPTION\n");
    fprintf(stdout, "FR file containing friendship relations ");
    fprintf(stdout, "between people\n");
    fprintf(stdout, "Pi name of someone in the friendships file\n");
    fprintf(stdout, "CR file containing conspiracies intentions\n");
    fprintf(stdout, "n maximum length of friendship paths\n");
}

void print_names(const name_list_t *names)
{
    size_t i = 0;

    fprintf(stdout, "Names:\n");
    for (i = 0; i < names->size; ++i)
        fprintf(stdout, "%s\n", names->items[i]);
}

void print_matrix(const int *mat, size_t n)
{
    size_t i = 0;
    size_t j = 0;

    fprintf(stdout, "Relationships:\n");
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            fprintf(stdout, "%d", mat[i * n + j]);
            if (j + 1 < n)
                fprintf(stdout, " ");
        }
        fprintf(stdout, "\n");
    }
}

void print_chain(const int *path, int len, const name_list_t *names)
{
    int i = 0;

    if (len <= 1)
        return;
    for (i = 0; i < len; ++i) {
        fprintf(stdout, "%s", names->items[path[i]]);
        if (i + 1 < len)
            fprintf(stdout, " -> ");
    }
    fprintf(stdout, "\n");
}


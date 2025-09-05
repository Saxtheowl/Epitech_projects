/*
** EPITECH PROJECT, 2025
** TextCount
** File description:
** print
*/

#include "text_count.h"

static void print_grouped_count(char_count_t *counts, int count_size, int count)
{
    int first = 1;
    int i = 0;

    for (i = 0; i < count_size; i++) {
        if (counts[i].count == count) {
            if (!first)
                printf(",");
            printf("%c", counts[i].character);
            first = 0;
        }
    }
    printf(":%d\n", count);
}

static void print_grouped_results(char_count_t *counts, int count_size,
    flags_t flags)
{
    int *printed = calloc(count_size, sizeof(int));
    int i = 0;

    if (flags.sort_by_count)
        sort_by_count(counts, count_size);
    else
        sort_by_appearance(counts, count_size);
    for (i = 0; i < count_size; i++) {
        if (!printed[i]) {
            print_grouped_count(counts, count_size, counts[i].count);
            for (int j = 0; j < count_size; j++) {
                if (counts[j].count == counts[i].count)
                    printed[j] = 1;
            }
        }
    }
    free(printed);
}

void print_results(char_count_t *counts, int count_size, flags_t flags)
{
    int i = 0;

    if (count_size == 0)
        return;
    if (flags.group_same_count) {
        print_grouped_results(counts, count_size, flags);
        return;
    }
    if (flags.sort_by_count)
        sort_by_count(counts, count_size);
    else
        sort_by_appearance(counts, count_size);
    for (i = 0; i < count_size; i++)
        printf("%c:%d\n", counts[i].character, counts[i].count);
}

int text_count(int argc, char **argv)
{
    flags_t flags;
    char *str = NULL;
    char *searched = NULL;
    char_count_t *counts = NULL;
    int count_size = 0;

    if (parse_arguments(argc, argv, &flags, &str, &searched) != 0)
        return 84;
    count_characters(str, searched, &counts, &count_size);
    print_results(counts, count_size, flags);
    free(counts);
    return 0;
}
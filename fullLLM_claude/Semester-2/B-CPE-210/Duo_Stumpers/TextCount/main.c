/*
** EPITECH PROJECT, 2024
** TextCount
** File description:
** Count character occurrences in a string
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    char character;
    int count;
    int first_appearance;
} char_count_t;

typedef struct {
    int r_flag;
    int t_flag;
    char *str;
    char *searched_chars;
} args_t;

void print_usage(void)
{
    fprintf(stderr, "Usage: ./text_count [-r] [-t] STR [SEARCHED_CHARACTERS]\n");
}

int parse_args(int argc, char **argv, args_t *args)
{
    int i = 1;
    
    args->r_flag = 0;
    args->t_flag = 0;
    args->str = NULL;
    args->searched_chars = NULL;
    
    while (i < argc && argv[i][0] == '-') {
        if (strcmp(argv[i], "-r") == 0) {
            args->r_flag = 1;
        } else if (strcmp(argv[i], "-t") == 0) {
            args->t_flag = 1;
        } else {
            print_usage();
            return 84;
        }
        i++;
    }
    
    if (i >= argc) {
        print_usage();
        return 84;
    }
    
    args->str = argv[i];
    if (i + 1 < argc)
        args->searched_chars = argv[i + 1];
    
    return 0;
}

int is_in_searched_chars(char c, char *searched_chars)
{
    int i;
    
    if (!searched_chars)
        return 1;
    
    for (i = 0; searched_chars[i]; i++) {
        if (searched_chars[i] == c)
            return 1;
    }
    return 0;
}

void count_characters(char *str, char *searched_chars, char_count_t *counts, int *unique_count)
{
    int i, j;
    int pos = 0;
    
    for (i = 0; str[i]; i++) {
        if (!is_in_searched_chars(str[i], searched_chars))
            continue;
            
        // Check if character already exists
        int found = 0;
        for (j = 0; j < pos; j++) {
            if (counts[j].character == str[i]) {
                counts[j].count++;
                found = 1;
                break;
            }
        }
        
        if (!found) {
            counts[pos].character = str[i];
            counts[pos].count = 1;
            counts[pos].first_appearance = i;
            pos++;
        }
    }
    
    // Add searched characters with 0 count if they don't appear
    if (searched_chars) {
        for (i = 0; searched_chars[i]; i++) {
            int found = 0;
            for (j = 0; j < pos; j++) {
                if (counts[j].character == searched_chars[i]) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                counts[pos].character = searched_chars[i];
                counts[pos].count = 0;
                counts[pos].first_appearance = 1000000; // Large number for sorting
                pos++;
            }
        }
    }
    
    *unique_count = pos;
}

int compare_by_count_desc(const void *a, const void *b)
{
    char_count_t *ca = (char_count_t *)a;
    char_count_t *cb = (char_count_t *)b;
    
    if (ca->count != cb->count)
        return cb->count - ca->count;
    return ca->first_appearance - cb->first_appearance;
}

int compare_by_appearance(const void *a, const void *b)
{
    char_count_t *ca = (char_count_t *)a;
    char_count_t *cb = (char_count_t *)b;
    
    return ca->first_appearance - cb->first_appearance;
}

void print_results(char_count_t *counts, int unique_count, int r_flag, int t_flag)
{
    int i, j;
    
    if (t_flag) {
        qsort(counts, unique_count, sizeof(char_count_t), compare_by_count_desc);
    } else {
        qsort(counts, unique_count, sizeof(char_count_t), compare_by_appearance);
    }
    
    if (r_flag) {
        // Group by count
        i = 0;
        while (i < unique_count) {
            int current_count = counts[i].count;
            int first_of_group = 1;
            
            for (j = i; j < unique_count && counts[j].count == current_count; j++) {
                if (!first_of_group)
                    printf(",");
                printf("%c", counts[j].character);
                first_of_group = 0;
            }
            printf(":%d\n", current_count);
            i = j;
        }
    } else {
        // Normal output
        for (i = 0; i < unique_count; i++) {
            printf("%c:%d\n", counts[i].character, counts[i].count);
        }
    }
}

int main(int argc, char **argv)
{
    args_t args;
    char_count_t counts[256];
    int unique_count = 0;
    
    if (parse_args(argc, argv, &args) != 0)
        return 84;
    
    if (strlen(args.str) == 0) {
        return 0;
    }
    
    if (args.searched_chars && strlen(args.searched_chars) == 0) {
        return 0;
    }
    
    count_characters(args.str, args.searched_chars, counts, &unique_count);
    print_results(counts, unique_count, args.r_flag, args.t_flag);
    
    return 0;
}
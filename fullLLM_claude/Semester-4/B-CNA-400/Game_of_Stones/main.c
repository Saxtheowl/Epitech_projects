/*
** EPITECH PROJECT, 2024
** Game of Stones
** File description:
** Main function and argument parsing
*/

#include "game_of_stones.h"

static void print_usage(void)
{
    printf("USAGE:\n");
    printf("    ./game_of_stones --links FR P1 P2\n");
    printf("        Calculate degree of separation between P1 and P2\n");
    printf("    ./game_of_stones --plots FR CR n\n");
    printf("        Analyze plots to save or betray the Crown\n");
    printf("\nDESCRIPTION:\n");
    printf("    FR    friendship report file\n");
    printf("    CR    conspiracy report file\n");
    printf("    P1    first person name\n");
    printf("    P2    second person name\n");
    printf("    n     maximum friendship distance\n");
}

static int is_valid_number(char *str)
{
    if (!str || *str == '\0')
        return 0;
    
    for (int i = 0; str[i]; i++) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}

static int parse_links_args(int argc, char **argv)
{
    if (argc != 5) {
        print_usage();
        return ERROR_EXIT;
    }
    
    return links_mode(argv[2], argv[3], argv[4]);
}

static int parse_plots_args(int argc, char **argv)
{
    if (argc != 5) {
        print_usage();
        return ERROR_EXIT;
    }
    
    if (!is_valid_number(argv[4])) {
        fprintf(stderr, "Error: n must be a valid number\n");
        return ERROR_EXIT;
    }
    
    int max_distance = atoi(argv[4]);
    if (max_distance < 0) {
        fprintf(stderr, "Error: n must be positive\n");
        return ERROR_EXIT;
    }
    
    return plots_mode(argv[2], argv[3], max_distance);
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        print_usage();
        return ERROR_EXIT;
    }
    
    if (strcmp(argv[1], "--links") == 0) {
        return parse_links_args(argc, argv);
    } else if (strcmp(argv[1], "--plots") == 0) {
        return parse_plots_args(argc, argv);
    } else {
        print_usage();
        return ERROR_EXIT;
    }
}
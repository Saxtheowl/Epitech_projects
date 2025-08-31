/*
** EPITECH PROJECT, 2024
** Matchstick
** File description:
** AI logic and strategy functions
*/

#include "../include/matchstick.h"

static int count_line_matches(game_t *game, int line_index)
{
    int i, count = 0;
    int matches_in_line = count_matches_in_line(line_index + 1);

    for (i = 0; i < matches_in_line; i++) {
        if (game->board[line_index][i] == 1)
            count++;
    }
    return count;
}

int calculate_nim_sum(game_t *game)
{
    int i, nim_sum = 0;

    for (i = 0; i < game->lines; i++) {
        int line_matches = count_line_matches(game, i);
        nim_sum ^= line_matches;
    }
    return nim_sum;
}

static void make_optimal_move(game_t *game)
{
    int i, line_matches, target;
    int nim_sum = calculate_nim_sum(game);

    for (i = 0; i < game->lines; i++) {
        line_matches = count_line_matches(game, i);
        if (line_matches == 0)
            continue;
            
        target = line_matches ^ nim_sum;
        if (target < line_matches) {
            int matches_to_remove = line_matches - target;
            if (matches_to_remove <= game->max_matches && matches_to_remove > 0) {
                printf("AI removed %d match(es) from line %d\n", 
                       matches_to_remove, i + 1);
                make_move(game, i + 1, matches_to_remove);
                return;
            }
        }
    }
    
    for (i = 0; i < game->lines; i++) {
        line_matches = count_line_matches(game, i);
        if (line_matches > 0) {
            int matches_to_remove = (line_matches > game->max_matches) ? 
                                   game->max_matches : line_matches;
            printf("AI removed %d match(es) from line %d\n", 
                   matches_to_remove, i + 1);
            make_move(game, i + 1, matches_to_remove);
            return;
        }
    }
}

static void make_random_move(game_t *game)
{
    int i, line_matches;
    int valid_lines[MAX_LINES];
    int valid_count = 0;

    for (i = 0; i < game->lines; i++) {
        line_matches = count_line_matches(game, i);
        if (line_matches > 0) {
            valid_lines[valid_count] = i;
            valid_count++;
        }
    }
    
    if (valid_count > 0) {
        int chosen_line_index = valid_lines[random() % valid_count];
        line_matches = count_line_matches(game, chosen_line_index);
        int matches_to_remove = (random() % 
                               ((line_matches > game->max_matches) ? 
                                game->max_matches : line_matches)) + 1;
        
        printf("AI removed %d match(es) from line %d\n", 
               matches_to_remove, chosen_line_index + 1);
        make_move(game, chosen_line_index + 1, matches_to_remove);
    }
}

void ai_move(game_t *game)
{
    int nim_sum = calculate_nim_sum(game);

    if (nim_sum != 0) {
        make_optimal_move(game);
    } else {
        make_random_move(game);
    }
}
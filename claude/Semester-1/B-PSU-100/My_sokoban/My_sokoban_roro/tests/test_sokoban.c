/*
** EPITECH PROJECT, 2025
** my_sokoban
** File description:
** Unit tests for sokoban game
*/

#include <criterion/criterion.h>
#include "sokoban.h"

Test(sokoban, check_player_position)
{
    sokoban_map_t *map;
    position_t *pos;
    
    map = make_map_from_string("##########\n"
                               "# #\n"
                               "# #\n"
                               "# PXO ###\n"
                               "# #\n"
                               "# OX #\n"
                               "##########\n");
    
    pos = get_player_position(map);
    cr_assert_neq(pos, NULL);
    cr_assert_eq(pos->x, 2);
    cr_assert_eq(pos->y, 3);
    
    free(pos);
    free_map(map);
}

Test(sokoban, map_validation_valid)
{
    sokoban_map_t *map;
    
    map = make_map_from_string("####\n"
                               "#PX#\n"
                               "#O #\n"
                               "####\n");
    
    cr_assert_neq(map, NULL);
    cr_assert_eq(validate_map(map), 1);
    
    free_map(map);
}

Test(sokoban, map_validation_invalid_no_player)
{
    sokoban_map_t *map;
    
    map = make_map_from_string("####\n"
                               "# X#\n"
                               "#O #\n"
                               "####\n");
    
    cr_assert_neq(map, NULL);
    cr_assert_eq(validate_map(map), 0);
    
    free_map(map);
}

Test(sokoban, map_validation_invalid_multiple_players)
{
    sokoban_map_t *map;
    
    map = make_map_from_string("####\n"
                               "#PX#\n"
                               "#OP#\n"
                               "####\n");
    
    cr_assert_neq(map, NULL);
    cr_assert_eq(validate_map(map), 0);
    
    free_map(map);
}

Test(sokoban, map_validation_invalid_no_boxes)
{
    sokoban_map_t *map;
    
    map = make_map_from_string("####\n"
                               "#P #\n"
                               "#O #\n"
                               "####\n");
    
    cr_assert_neq(map, NULL);
    cr_assert_eq(validate_map(map), 0);
    
    free_map(map);
}

Test(sokoban, map_validation_invalid_no_targets)
{
    sokoban_map_t *map;
    
    map = make_map_from_string("####\n"
                               "#PX#\n"
                               "#  #\n"
                               "####\n");
    
    cr_assert_neq(map, NULL);
    cr_assert_eq(validate_map(map), 0);
    
    free_map(map);
}

Test(sokoban, map_validation_invalid_character)
{
    sokoban_map_t *map;
    
    map = make_map_from_string("####\n"
                               "#PX#\n"
                               "#OZ#\n"
                               "####\n");
    
    cr_assert_neq(map, NULL);
    cr_assert_eq(validate_map(map), 0);
    
    free_map(map);
}

Test(sokoban, check_win_condition_not_won)
{
    sokoban_map_t *map;
    
    map = make_map_from_string("####\n"
                               "#PX#\n"
                               "#O #\n"
                               "####\n");
    
    cr_assert_neq(map, NULL);
    cr_assert_eq(check_win_condition(map), 0);
    
    free_map(map);
}

Test(sokoban, game_initialization)
{
    sokoban_map_t *map;
    game_t *game;
    
    map = make_map_from_string("####\n"
                               "#PX#\n"
                               "#O #\n"
                               "####\n");
    
    cr_assert_neq(map, NULL);
    
    game = malloc(sizeof(game_t));
    game->map = map;
    game->game_state = EXIT_SUCCESS;
    game->is_running = true;
    
    cr_assert_neq(game, NULL);
    cr_assert_eq(game->is_running, true);
    cr_assert_eq(game->game_state, EXIT_SUCCESS);
    
    free_game(game);
}

Test(sokoban, string_functions)
{
    cr_assert_eq(my_strlen("hello"), 5);
    cr_assert_eq(my_strlen(""), 0);
    cr_assert_eq(my_strlen(NULL), 0);
    
    cr_assert_eq(my_strcmp("hello", "hello"), 0);
    cr_assert_neq(my_strcmp("hello", "world"), 0);
    
    char *dup = my_strdup("test");
    cr_assert_neq(dup, NULL);
    cr_assert_eq(my_strcmp(dup, "test"), 0);
    free(dup);
}
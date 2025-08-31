/*
** EPITECH PROJECT, 2024
** Matchstick
** File description:
** Test program for matchstick functionality
*/

#include "../include/matchstick.h"
#include <assert.h>

void test_game_initialization(void)
{
    game_t *game;

    printf("Testing game initialization...\n");
    
    game = init_game(4, 3);
    assert(game != NULL);
    assert(game->lines == 4);
    assert(game->max_matches == 3);
    assert(game->current_player == 0);
    
    assert(count_matches_in_line(1) == 1);
    assert(count_matches_in_line(2) == 3);
    assert(count_matches_in_line(3) == 5);
    assert(count_matches_in_line(4) == 7);
    
    cleanup_game(game);
    printf("✓ Game initialization tests passed\n");
}

void test_utility_functions(void)
{
    printf("Testing utility functions...\n");
    
    assert(my_atoi("123") == 123);
    assert(my_atoi("-456") == -456);
    assert(my_atoi("0") == 0);
    assert(my_atoi(" 42 ") == 42);
    
    printf("✓ Utility function tests passed\n");
}

void test_game_logic(void)
{
    game_t *game;
    
    printf("Testing game logic...\n");
    
    game = init_game(3, 2);
    assert(game != NULL);
    
    assert(is_game_over(game) == 0);
    
    assert(validate_move(game, 1, 1) == 0);
    assert(validate_move(game, 0, 1) == -1);
    assert(validate_move(game, 4, 1) == -1);
    assert(validate_move(game, 1, 3) == -1);
    
    make_move(game, 1, 1);
    
    cleanup_game(game);
    printf("✓ Game logic tests passed\n");
}

void test_nim_calculation(void)
{
    game_t *game;
    int nim_sum;
    
    printf("Testing NIM sum calculation...\n");
    
    game = init_game(3, 2);
    assert(game != NULL);
    
    nim_sum = calculate_nim_sum(game);
    assert(nim_sum >= 0);
    
    cleanup_game(game);
    printf("✓ NIM calculation tests passed\n");
}

void test_argument_validation(void)
{
    char *valid_args1[] = {"matchstick", "4", "3"};
    char *invalid_args1[] = {"matchstick", "1", "3"};
    char *invalid_args2[] = {"matchstick", "4", "0"};
    char *invalid_args3[] = {"matchstick", "100", "3"};
    
    printf("Testing argument validation...\n");
    
    assert(check_arguments(3, valid_args1) == 0);
    assert(check_arguments(3, invalid_args1) == -1);
    assert(check_arguments(3, invalid_args2) == -1);
    assert(check_arguments(3, invalid_args3) == -1);
    assert(check_arguments(2, valid_args1) == -1);
    
    printf("✓ Argument validation tests passed\n");
}

int main(void)
{
    printf("=== Matchstick Test Suite ===\n\n");
    
    test_game_initialization();
    test_utility_functions();
    test_game_logic();
    test_nim_calculation();
    test_argument_validation();
    
    printf("\n=== All tests completed ===\n");
    return 0;
}
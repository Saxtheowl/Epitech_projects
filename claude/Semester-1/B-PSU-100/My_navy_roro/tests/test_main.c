/*
** EPITECH PROJECT, 2024
** My_navy
** File description:
** Test program for my_navy functionality
*/

#include "../include/my_navy.h"
#include <stdio.h>
#include <assert.h>

game_t *g_game = NULL;

void test_position_validation(void)
{
    printf("Testing position validation...\n");
    
    assert(is_valid_position("A1") == 1);
    assert(is_valid_position("H8") == 1);
    assert(is_valid_position("D4") == 1);
    assert(is_valid_position("I1") == 0);
    assert(is_valid_position("A9") == 0);
    assert(is_valid_position("Z5") == 0);
    assert(is_valid_position("A") == 0);
    assert(is_valid_position("11") == 0);
    
    printf("✓ Position validation tests passed\n");
}

void test_position_parsing(void)
{
    int x, y;
    
    printf("Testing position parsing...\n");
    
    parse_position("A1", &x, &y);
    assert(x == 0 && y == 0);
    
    parse_position("H8", &x, &y);
    assert(x == 7 && y == 7);
    
    parse_position("D4", &x, &y);
    assert(x == 3 && y == 3);
    
    printf("✓ Position parsing tests passed\n");
}

void test_string_functions(void)
{
    printf("Testing string utility functions...\n");
    
    assert(my_strlen("hello") == 5);
    assert(my_strlen("") == 0);
    assert(my_strlen(NULL) == 0);
    
    assert(my_strcmp("abc", "abc") == 0);
    assert(my_strcmp("abc", "def") < 0);
    assert(my_strcmp("def", "abc") > 0);
    
    printf("✓ String function tests passed\n");
}

void test_board_initialization(void)
{
    game_t game = {0};
    int i, j;
    
    printf("Testing board initialization...\n");
    
    init_boards(&game);
    
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            assert(game.my_board[i][j] == '.');
            assert(game.enemy_board[i][j] == '.');
        }
    }
    
    printf("✓ Board initialization tests passed\n");
}

void test_ship_creation(void)
{
    game_t game = {0};
    
    printf("Testing ship structure creation...\n");
    
    game.ships[0].length = 2;
    game.ships[0].start_x = 0;
    game.ships[0].start_y = 0;
    game.ships[0].end_x = 1;
    game.ships[0].end_y = 0;
    game.ships[0].hits = 0;
    
    assert(game.ships[0].length == 2);
    assert(game.ships[0].start_x == 0);
    assert(game.ships[0].end_x == 1);
    
    printf("✓ Ship creation tests passed\n");
}

int main(void)
{
    printf("=== My_navy Test Suite ===\n\n");
    
    test_position_validation();
    test_position_parsing();
    test_string_functions();
    test_board_initialization();
    test_ship_creation();
    
    printf("\n=== All tests completed successfully ===\n");
    return 0;
}
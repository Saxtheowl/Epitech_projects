/*
** EPITECH PROJECT, 2024
** My_sokoban
** File description:
** Test program for my_sokoban functionality
*/

#include "../include/my_sokoban.h"
#include <stdio.h>
#include <assert.h>

void test_player_position(void)
{
    map_t *map;
    position_t *pos;

    printf("Testing player position detection...\n");
    
    map = make_map_from_string("##########\n"
                               "#        #\n"
                               "#        #\n"
                               "#  PXO   #\n"
                               "#        #\n"
                               "#   OX   #\n"
                               "##########\n");
    
    assert(map != NULL);
    pos = get_player_position(map);
    assert(pos != NULL);
    assert(pos->x == 3);
    assert(pos->y == 3);
    
    free(pos);
    free_map(map);
    printf("✓ Player position tests passed\n");
}

void test_map_validation(void)
{
    map_t *map;

    printf("Testing map validation...\n");
    
    map = make_map_from_string("##########\n"
                               "#  O     #\n"
                               "#  P  ## #\n"
                               "#        #\n"
                               "#######  #\n"
                               "#  O ##  #\n"
                               "#    ##  #\n"
                               "#        #\n"
                               "#   XX   #\n"
                               "#   #    #\n"
                               "##########\n");
    
    assert(map != NULL);
    assert(validate_map(map) == 0);
    
    free_map(map);
    printf("✓ Map validation tests passed\n");
}

void test_character_counting(void)
{
    map_t *map;

    printf("Testing character counting...\n");
    
    map = make_map_from_string("##########\n"
                               "#  O     #\n"
                               "#  P     #\n"
                               "#   XX   #\n"
                               "##########\n");
    
    assert(map != NULL);
    assert(count_char_in_map(map, 'P') == 1);
    assert(count_char_in_map(map, 'X') == 2);
    assert(count_char_in_map(map, 'O') == 1);
    printf("Wall count: %d\n", count_char_in_map(map, '#'));
    
    free_map(map);
    printf("✓ Character counting tests passed\n");
}

void test_movement_validation(void)
{
    map_t *map;

    printf("Testing movement validation...\n");
    
    map = make_map_from_string("##########\n"
                               "#        #\n"
                               "#  P X   #\n"
                               "#        #\n"
                               "##########\n");
    
    assert(map != NULL);
    assert(can_move_to(map, 2, 2) == 1);  // Empty space
    assert(can_move_to(map, 0, 2) == 0);  // Wall
    assert(can_move_to(map, 5, 2) == 0);  // Box
    assert(can_push_box(map, 5, 2, 1, 0) == 1);  // Can push box right
    assert(can_push_box(map, 5, 2, -1, 0) == 1); // Can push box left
    
    free_map(map);
    printf("✓ Movement validation tests passed\n");
}

void test_win_condition(void)
{
    map_t *map;

    printf("Testing win condition...\n");
    
    map = make_map_from_string("##########\n"
                               "#        #\n"
                               "#  P *   #\n"
                               "#        #\n"
                               "##########\n");
    
    assert(map != NULL);
    update_box_storage_count(map);
    assert(check_win_condition(map) == 1);  // All boxes on storage
    
    free_map(map);
    
    map = make_map_from_string("##########\n"
                               "#        #\n"
                               "#  P X O #\n"
                               "#        #\n"
                               "##########\n");
    
    assert(map != NULL);
    update_box_storage_count(map);
    assert(check_win_condition(map) == 0);  // Box not on storage
    
    free_map(map);
    printf("✓ Win condition tests passed\n");
}

int main(void)
{
    printf("=== My_sokoban Test Suite ===\n\n");
    
    test_player_position();
    test_map_validation();
    test_character_counting();
    test_movement_validation();
    test_win_condition();
    
    printf("\n=== All tests completed successfully ===\n");
    return 0;
}
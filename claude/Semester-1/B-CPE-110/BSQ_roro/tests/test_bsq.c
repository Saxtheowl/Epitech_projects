/*
** EPITECH PROJECT, 2024
** test_bsq.c
** File description:
** Unit tests for BSQ project
*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/bsq.h"

static void test_simple_map(void)
{
    map_t map = {NULL, 0, 0, NULL};
    char *content = "3\n...\n.o.\n...\n";
    square_t square;

    printf("Testing simple 3x3 map...\n");
    if (parse_map(content, &map) == 0) {
        square = find_biggest_square(&map);
        printf("Found square: size=%d, row=%d, col=%d\n", 
               square.size, square.row, square.col);
        print_result(&map, square);
        free_map(&map);
        printf("PASS\n\n");
    } else {
        printf("FAIL: Map parsing failed\n\n");
    }
}

static void test_no_obstacle_map(void)
{
    map_t map = {NULL, 0, 0, NULL};
    char *content = "4\n....\n....\n....\n....\n";
    square_t square;

    printf("Testing 4x4 map with no obstacles...\n");
    if (parse_map(content, &map) == 0) {
        square = find_biggest_square(&map);
        printf("Found square: size=%d, row=%d, col=%d\n", 
               square.size, square.row, square.col);
        print_result(&map, square);
        free_map(&map);
        printf("PASS\n\n");
    } else {
        printf("FAIL: Map parsing failed\n\n");
    }
}

static void test_single_cell_map(void)
{
    map_t map = {NULL, 0, 0, NULL};
    char *content = "1\n.\n";
    square_t square;

    printf("Testing single cell map...\n");
    if (parse_map(content, &map) == 0) {
        square = find_biggest_square(&map);
        printf("Found square: size=%d, row=%d, col=%d\n", 
               square.size, square.row, square.col);
        print_result(&map, square);
        free_map(&map);
        printf("PASS\n\n");
    } else {
        printf("FAIL: Map parsing failed\n\n");
    }
}

int main(void)
{
    printf("Running BSQ unit tests...\n\n");
    test_simple_map();
    test_no_obstacle_map();
    test_single_cell_map();
    printf("All tests completed!\n");
    return 0;
}
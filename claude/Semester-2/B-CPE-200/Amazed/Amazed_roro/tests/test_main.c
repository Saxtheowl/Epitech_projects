/*
** EPITECH PROJECT, 2024
** Amazed
** File description:
** Test program for amazed functionality
*/

#include "../include/amazed.h"
#include <assert.h>

void test_utility_functions(void)
{
    char *str;
    
    printf("Testing utility functions...\n");
    
    assert(my_strlen("hello") == 5);
    assert(my_strlen("") == 0);
    assert(my_strlen(NULL) == 0);
    
    assert(my_strcmp("abc", "abc") == 0);
    assert(my_strcmp("abc", "def") < 0);
    assert(my_strcmp("def", "abc") > 0);
    
    str = my_strdup("test");
    assert(str != NULL);
    assert(my_strcmp(str, "test") == 0);
    free(str);
    
    printf("✓ Utility function tests passed\n");
}

void test_maze_creation(void)
{
    maze_t *maze;
    
    printf("Testing maze creation...\n");
    
    maze = create_maze();
    assert(maze != NULL);
    assert(maze->robot_count == 0);
    assert(maze->room_count == 0);
    assert(maze->tunnel_count == 0);
    assert(maze->start_room == -1);
    assert(maze->end_room == -1);
    
    cleanup_maze(maze);
    
    printf("✓ Maze creation tests passed\n");
}

void test_room_management(void)
{
    maze_t *maze;
    int room_id;
    
    printf("Testing room management...\n");
    
    maze = create_maze();
    assert(maze != NULL);
    
    room_id = add_room(maze, "start", 0, 0, 1, 0);
    assert(room_id == 0);
    assert(maze->room_count == 1);
    assert(maze->start_room == 0);
    assert(my_strcmp(maze->rooms[0].name, "start") == 0);
    
    room_id = add_room(maze, "end", 10, 10, 0, 1);
    assert(room_id == 1);
    assert(maze->room_count == 2);
    assert(maze->end_room == 1);
    
    assert(find_room_by_name(maze, "start") == 0);
    assert(find_room_by_name(maze, "end") == 1);
    assert(find_room_by_name(maze, "nonexistent") == -1);
    
    add_connection(maze, 0, 1);
    assert(maze->rooms[0].connection_count == 1);
    assert(maze->rooms[1].connection_count == 1);
    assert(maze->rooms[0].connections[0] == 1);
    assert(maze->rooms[1].connections[0] == 0);
    
    cleanup_maze(maze);
    
    printf("✓ Room management tests passed\n");
}

void test_pathfinding(void)
{
    maze_t *maze;
    int *path;
    int path_length;
    
    printf("Testing pathfinding...\n");
    
    maze = create_maze();
    assert(maze != NULL);
    
    add_room(maze, "0", 0, 0, 1, 0);
    add_room(maze, "1", 5, 0, 0, 1);
    add_room(maze, "2", 10, 0, 0, 0);
    
    add_connection(maze, 0, 2);
    add_connection(maze, 2, 1);
    
    create_adjacency_matrix(maze);
    assert(maze->adjacency_matrix != NULL);
    assert(maze->adjacency_matrix[0][2] == 1);
    assert(maze->adjacency_matrix[2][1] == 1);
    assert(maze->adjacency_matrix[0][1] == 0);
    
    path = find_shortest_path(maze, 0, 1, &path_length);
    assert(path != NULL);
    assert(path_length == 3);
    assert(path[0] == 0);
    assert(path[1] == 2);
    assert(path[2] == 1);
    
    free(path);
    cleanup_maze(maze);
    
    printf("✓ Pathfinding tests passed\n");
}

void test_robot_count_parsing(void)
{
    maze_t *maze;
    char line[] = "42";
    
    printf("Testing robot count parsing...\n");
    
    maze = create_maze();
    assert(maze != NULL);
    
    assert(parse_number_of_robots(maze, line) == 0);
    assert(maze->robot_count == 42);
    
    cleanup_maze(maze);
    
    printf("✓ Robot count parsing tests passed\n");
}

int main(void)
{
    printf("=== Amazed Test Suite ===\n\n");
    
    test_utility_functions();
    test_maze_creation();
    test_room_management();
    test_pathfinding();
    test_robot_count_parsing();
    
    printf("\n=== All tests completed ===\n");
    return 0;
}
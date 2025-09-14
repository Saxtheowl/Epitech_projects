#include "solver.h"

int is_valid_move(maze_t *maze, int x, int y, char **visited)
{
    if (x < 0 || x >= maze->width || y < 0 || y >= maze->height)
        return 0;
    if (maze->grid[y][x] == 'X')
        return 0;
    if (visited[y][x])
        return 0;
    return 1;
}

int dfs(maze_t *maze, int x, int y, char **visited)
{
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int i, next_x, next_y;
    
    if (x == maze->width - 1 && y == maze->height - 1) {
        maze->grid[y][x] = 'o';
        return 1;
    }
    
    visited[y][x] = 1;
    
    for (i = 0; i < 4; i++) {
        next_x = x + directions[i][0];
        next_y = y + directions[i][1];
        
        if (is_valid_move(maze, next_x, next_y, visited)) {
            if (dfs(maze, next_x, next_y, visited)) {
                maze->grid[y][x] = 'o';
                return 1;
            }
        }
    }
    
    return 0;
}

int solve_maze(maze_t *maze)
{
    char **visited;
    int i, j, result;
    
    if (!maze || maze->width <= 0 || maze->height <= 0)
        return 0;
    
    if (maze->grid[0][0] == 'X' || 
        maze->grid[maze->height - 1][maze->width - 1] == 'X')
        return 0;
    
    visited = malloc(sizeof(char *) * maze->height);
    if (!visited)
        return 0;
    
    for (i = 0; i < maze->height; i++) {
        visited[i] = calloc(maze->width, sizeof(char));
        if (!visited[i]) {
            for (j = 0; j < i; j++)
                free(visited[j]);
            free(visited);
            return 0;
        }
    }
    
    result = dfs(maze, 0, 0, visited);
    
    for (i = 0; i < maze->height; i++)
        free(visited[i]);
    free(visited);
    
    return result;
}

void print_maze(maze_t *maze)
{
    int i;
    
    if (!maze)
        return;
    
    for (i = 0; i < maze->height; i++) {
        printf("%s", maze->grid[i]);
        if (i < maze->height - 1)
            printf("\n");
    }
}
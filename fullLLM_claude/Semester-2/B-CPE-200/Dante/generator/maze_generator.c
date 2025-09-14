#include "generator.h"

maze_t *create_maze(int width, int height, int perfect)
{
    maze_t *maze;
    int i, j;
    
    maze = malloc(sizeof(maze_t));
    if (!maze)
        return NULL;
    
    maze->width = width;
    maze->height = height;
    maze->perfect = perfect;
    
    maze->grid = malloc(sizeof(char *) * height);
    if (!maze->grid) {
        free(maze);
        return NULL;
    }
    
    for (i = 0; i < height; i++) {
        maze->grid[i] = malloc(width + 1);
        if (!maze->grid[i]) {
            for (j = 0; j < i; j++)
                free(maze->grid[j]);
            free(maze->grid);
            free(maze);
            return NULL;
        }
        
        for (j = 0; j < width; j++) {
            maze->grid[i][j] = 'X';
        }
        maze->grid[i][width] = '\0';
    }
    
    return maze;
}

void shuffle_directions(int directions[][2], int count)
{
    int i, j, temp[2];
    
    for (i = 0; i < count; i++) {
        j = rand() % count;
        temp[0] = directions[i][0];
        temp[1] = directions[i][1];
        directions[i][0] = directions[j][0];
        directions[i][1] = directions[j][1];
        directions[j][0] = temp[0];
        directions[j][1] = temp[1];
    }
}

int is_valid_cell(maze_t *maze, int x, int y)
{
    return (x >= 0 && x < maze->width && y >= 0 && y < maze->height);
}

void carve_path(maze_t *maze, int x, int y, char **visited)
{
    int directions[4][2] = {{0, 2}, {2, 0}, {0, -2}, {-2, 0}};
    int i, next_x, next_y, wall_x, wall_y;
    
    visited[y][x] = 1;
    maze->grid[y][x] = '*';
    
    shuffle_directions(directions, 4);
    
    for (i = 0; i < 4; i++) {
        next_x = x + directions[i][0];
        next_y = y + directions[i][1];
        
        if (is_valid_cell(maze, next_x, next_y) && !visited[next_y][next_x]) {
            wall_x = x + directions[i][0] / 2;
            wall_y = y + directions[i][1] / 2;
            
            maze->grid[wall_y][wall_x] = '*';
            
            carve_path(maze, next_x, next_y, visited);
        }
    }
}

void generate_perfect_maze(maze_t *maze)
{
    char **visited;
    int i, j;
    
    visited = malloc(sizeof(char *) * maze->height);
    if (!visited)
        return;
    
    for (i = 0; i < maze->height; i++) {
        visited[i] = calloc(maze->width, sizeof(char));
        if (!visited[i]) {
            for (j = 0; j < i; j++)
                free(visited[j]);
            free(visited);
            return;
        }
    }
    
    carve_path(maze, 0, 0, visited);
    
    maze->grid[maze->height - 1][maze->width - 1] = '*';
    
    for (i = 0; i < maze->height; i++)
        free(visited[i]);
    free(visited);
}

void generate_imperfect_maze(maze_t *maze)
{
    int i, x, y, loops;
    
    generate_perfect_maze(maze);
    
    loops = (maze->width * maze->height) / 20;
    
    for (i = 0; i < loops; i++) {
        x = rand() % maze->width;
        y = rand() % maze->height;
        
        if (maze->grid[y][x] == 'X') {
            int neighbors = 0;
            
            if (x > 0 && maze->grid[y][x-1] == '*') neighbors++;
            if (x < maze->width-1 && maze->grid[y][x+1] == '*') neighbors++;
            if (y > 0 && maze->grid[y-1][x] == '*') neighbors++;
            if (y < maze->height-1 && maze->grid[y+1][x] == '*') neighbors++;
            
            if (neighbors >= 2) {
                maze->grid[y][x] = '*';
            }
        }
    }
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

void free_maze(maze_t *maze)
{
    int i;
    
    if (!maze)
        return;
    
    if (maze->grid) {
        for (i = 0; i < maze->height; i++) {
            free(maze->grid[i]);
        }
        free(maze->grid);
    }
    free(maze);
}
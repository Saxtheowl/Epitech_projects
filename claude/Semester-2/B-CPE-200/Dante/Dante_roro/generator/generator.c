/*
** EPITECH PROJECT, 2024
** Dante's Star
** File description:
** Maze generator using recursive backtracking
*/

#include "../include/dante.h"

maze_t *create_maze(int width, int height)
{
    maze_t *maze = malloc(sizeof(maze_t));
    int i, j;

    if (!maze)
        return NULL;

    maze->width = width;
    maze->height = height;
    maze->grid = malloc(height * sizeof(char *));

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
            maze->grid[i][j] = WALL;
        }
        maze->grid[i][width] = '\0';
    }

    return maze;
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

void shuffle_directions(int *directions, int count)
{
    int i, j, temp;

    for (i = count - 1; i > 0; i--) {
        j = rand() % (i + 1);
        temp = directions[i];
        directions[i] = directions[j];
        directions[j] = temp;
    }
}

int has_unvisited_neighbors(maze_t *maze, int x, int y, char **visited)
{
    int dx[] = {0, 0, 2, -2};
    int dy[] = {2, -2, 0, 0};
    int i, nx, ny;

    for (i = 0; i < 4; i++) {
        nx = x + dx[i];
        ny = y + dy[i];
        
        if (nx >= 0 && nx < maze->width && ny >= 0 && ny < maze->height) {
            if (!visited[ny][nx])
                return 1;
        }
    }
    return 0;
}

void recursive_backtrack(maze_t *maze, int x, int y, char **visited)
{
    int directions[] = {0, 1, 2, 3};
    int dx[] = {0, 0, 2, -2};
    int dy[] = {2, -2, 0, 0};
    int i, nx, ny, wx, wy;

    visited[y][x] = 1;
    maze->grid[y][x] = PATH;
    
    shuffle_directions(directions, 4);

    for (i = 0; i < 4; i++) {
        nx = x + dx[directions[i]];
        ny = y + dy[directions[i]];

        if (nx >= 0 && nx < maze->width && ny >= 0 && ny < maze->height && !visited[ny][nx]) {
            wx = x + dx[directions[i]] / 2;
            wy = y + dy[directions[i]] / 2;
            
            maze->grid[wy][wx] = PATH;
            recursive_backtrack(maze, nx, ny, visited);
        }
    }
}

void generate_perfect_maze(maze_t *maze)
{
    char **visited;
    int i, j;

    visited = malloc(maze->height * sizeof(char *));
    for (i = 0; i < maze->height; i++) {
        visited[i] = malloc(maze->width * sizeof(char));
        for (j = 0; j < maze->width; j++) {
            visited[i][j] = 0;
        }
    }

    recursive_backtrack(maze, 0, 0, visited);

    maze->grid[maze->height - 1][maze->width - 1] = PATH;

    for (i = 0; i < maze->height; i++) {
        free(visited[i]);
    }
    free(visited);
}

void generate_imperfect_maze(maze_t *maze)
{
    int i, extra_paths;

    generate_perfect_maze(maze);

    extra_paths = (maze->width * maze->height) / 20;
    
    for (i = 0; i < extra_paths; i++) {
        int x = rand() % maze->width;
        int y = rand() % maze->height;
        
        if (maze->grid[y][x] == WALL) {
            int neighbors = 0;
            
            if (x > 0 && maze->grid[y][x-1] == PATH) neighbors++;
            if (x < maze->width-1 && maze->grid[y][x+1] == PATH) neighbors++;
            if (y > 0 && maze->grid[y-1][x] == PATH) neighbors++;
            if (y < maze->height-1 && maze->grid[y+1][x] == PATH) neighbors++;
            
            if (neighbors >= 2) {
                maze->grid[y][x] = PATH;
            }
        }
    }
}

void print_maze(maze_t *maze)
{
    int i;

    for (i = 0; i < maze->height; i++) {
        printf("%s", maze->grid[i]);
        if (i < maze->height - 1)
            printf("\n");
    }
}

int main(int argc, char **argv)
{
    maze_t *maze;
    int width, height;
    int perfect = 0;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s width height [perfect]\n", argv[0]);
        return 84;
    }

    width = atoi(argv[1]);
    height = atoi(argv[2]);
    
    if (width <= 0 || height <= 0) {
        fprintf(stderr, "Error: Invalid dimensions\n");
        return 84;
    }

    if (argc > 3 && strcmp(argv[3], "perfect") == 0) {
        perfect = 1;
    }

    srand(time(NULL));
    
    maze = create_maze(width, height);
    if (!maze) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return 84;
    }

    if (perfect) {
        generate_perfect_maze(maze);
    } else {
        generate_imperfect_maze(maze);
    }

    print_maze(maze);
    free_maze(maze);

    return 0;
}
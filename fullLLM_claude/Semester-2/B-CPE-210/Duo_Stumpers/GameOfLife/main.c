/*
** EPITECH PROJECT, 2024
** Game of Life
** File description:
** Conway's Game of Life implementation
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    char **grid;
    int width;
    int height;
} game_t;

void print_usage(void)
{
    fprintf(stderr, "Usage: ./gameoflife [map_file] [iterations]\n");
}

int is_valid_number(char *str)
{
    int i;
    
    for (i = 0; str[i]; i++) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}

void free_grid(game_t *game)
{
    int i;
    
    if (game->grid) {
        for (i = 0; i < game->height; i++) {
            free(game->grid[i]);
        }
        free(game->grid);
    }
}

int get_file_dimensions(FILE *file, int *width, int *height)
{
    char buffer[1024];
    *height = 0;
    *width = 0;
    
    while (fgets(buffer, sizeof(buffer), file)) {
        int line_len = strlen(buffer);
        if (line_len > 0 && buffer[line_len - 1] == '\n')
            buffer[line_len - 1] = '\0';
        
        int buffer_len = strlen(buffer);
        if (buffer_len > *width)
            *width = buffer_len;
        (*height)++;
    }
    
    return (*width > 0 && *height > 0) ? 0 : -1;
}

int load_map(char *filename, game_t *game)
{
    FILE *file = fopen(filename, "r");
    char buffer[1024];
    int i, j;
    
    if (!file) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        return 84;
    }
    
    if (get_file_dimensions(file, &game->width, &game->height) != 0) {
        fclose(file);
        return 84;
    }
    
    rewind(file);
    
    game->grid = malloc(sizeof(char*) * game->height);
    if (!game->grid) {
        fclose(file);
        return 84;
    }
    
    for (i = 0; i < game->height; i++) {
        game->grid[i] = malloc(sizeof(char) * (game->width + 1));
        if (!game->grid[i]) {
            free_grid(game);
            fclose(file);
            return 84;
        }
        
        // Initialize with dots
        for (j = 0; j < game->width; j++) {
            game->grid[i][j] = '.';
        }
        game->grid[i][game->width] = '\0';
    }
    
    // Read the actual content
    i = 0;
    while (fgets(buffer, sizeof(buffer), file) && i < game->height) {
        int line_len = strlen(buffer);
        if (line_len > 0 && buffer[line_len - 1] == '\n')
            buffer[line_len - 1] = '\0';
        
        int buffer_len = strlen(buffer);
        for (j = 0; j < buffer_len && j < game->width; j++) {
            if (buffer[j] == 'X' || buffer[j] == '.')
                game->grid[i][j] = buffer[j];
        }
        i++;
    }
    
    fclose(file);
    return 0;
}

int count_neighbors(game_t *game, int row, int col)
{
    int count = 0;
    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int i;
    
    for (i = 0; i < 8; i++) {
        int new_row = row + dr[i];
        int new_col = col + dc[i];
        
        if (new_row >= 0 && new_row < game->height && 
            new_col >= 0 && new_col < game->width) {
            if (game->grid[new_row][new_col] == 'X')
                count++;
        }
    }
    
    return count;
}

void evolve_generation(game_t *game)
{
    char **new_grid;
    int i, j;
    
    // Allocate new grid
    new_grid = malloc(sizeof(char*) * game->height);
    if (!new_grid)
        return;
    
    for (i = 0; i < game->height; i++) {
        new_grid[i] = malloc(sizeof(char) * (game->width + 1));
        if (!new_grid[i]) {
            for (j = 0; j < i; j++)
                free(new_grid[j]);
            free(new_grid);
            return;
        }
        new_grid[i][game->width] = '\0';
    }
    
    // Apply Game of Life rules
    for (i = 0; i < game->height; i++) {
        for (j = 0; j < game->width; j++) {
            int neighbors = count_neighbors(game, i, j);
            char current = game->grid[i][j];
            
            if (current == 'X') {
                // Live cell
                if (neighbors == 2 || neighbors == 3) {
                    new_grid[i][j] = 'X'; // Survives
                } else {
                    new_grid[i][j] = '.'; // Dies
                }
            } else {
                // Empty cell
                if (neighbors == 3) {
                    new_grid[i][j] = 'X'; // Birth
                } else {
                    new_grid[i][j] = '.'; // Stays empty
                }
            }
        }
    }
    
    // Replace old grid with new grid
    for (i = 0; i < game->height; i++) {
        free(game->grid[i]);
        game->grid[i] = new_grid[i];
    }
    free(new_grid);
}

void print_grid(game_t *game)
{
    int i;
    
    for (i = 0; i < game->height; i++) {
        printf("%s\n", game->grid[i]);
    }
}

int main(int argc, char **argv)
{
    game_t game;
    int iterations, i;
    
    if (argc != 3) {
        print_usage();
        return 84;
    }
    
    if (!is_valid_number(argv[2])) {
        print_usage();
        return 84;
    }
    
    iterations = atoi(argv[2]);
    
    if (load_map(argv[1], &game) != 0) {
        return 84;
    }
    
    // Run the specified number of iterations
    for (i = 0; i < iterations; i++) {
        evolve_generation(&game);
    }
    
    print_grid(&game);
    free_grid(&game);
    
    return 0;
}
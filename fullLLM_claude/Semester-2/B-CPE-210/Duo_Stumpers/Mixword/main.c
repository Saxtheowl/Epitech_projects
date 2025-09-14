/*
** EPITECH PROJECT, 2024
** MixWord
** File description:
** Word search puzzle generator
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100

typedef struct {
    char **words;
    int word_count;
} dictionary_t;

typedef struct {
    char **grid;
    int size;
    int words_placed;
} grid_t;

typedef struct {
    int dx, dy;
} direction_t;

direction_t directions[8] = {
    {0, 1},   // right
    {0, -1},  // left
    {1, 0},   // down
    {-1, 0},  // up
    {1, 1},   // down-right
    {1, -1},  // down-left
    {-1, 1},  // up-right
    {-1, -1}  // up-left
};

void print_usage(void)
{
    fprintf(stderr, "Usage: ./mixword -f FILE [-s SIZE]\n");
}

int load_dictionary(char *filename, dictionary_t *dict)
{
    FILE *file = fopen(filename, "r");
    char buffer[MAX_WORD_LEN];
    
    if (!file) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        return 84;
    }
    
    dict->words = malloc(sizeof(char*) * MAX_WORDS);
    if (!dict->words) {
        fclose(file);
        return 84;
    }
    
    dict->word_count = 0;
    
    while (fgets(buffer, sizeof(buffer), file) && dict->word_count < MAX_WORDS) {
        int len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
            buffer[len - 1] = '\0';
        
        if (strlen(buffer) == 0)
            continue;
        
        dict->words[dict->word_count] = malloc(strlen(buffer) + 1);
        if (dict->words[dict->word_count]) {
            strcpy(dict->words[dict->word_count], buffer);
            dict->word_count++;
        }
    }
    
    fclose(file);
    return 0;
}

void free_dictionary(dictionary_t *dict)
{
    int i;
    
    if (dict->words) {
        for (i = 0; i < dict->word_count; i++) {
            free(dict->words[i]);
        }
        free(dict->words);
    }
}

int init_grid(grid_t *grid, int size)
{
    int i, j;
    
    grid->size = size;
    grid->words_placed = 0;
    
    grid->grid = malloc(sizeof(char*) * size);
    if (!grid->grid)
        return 84;
    
    for (i = 0; i < size; i++) {
        grid->grid[i] = malloc(sizeof(char) * (size + 1));
        if (!grid->grid[i])
            return 84;
        for (j = 0; j < size; j++) {
            grid->grid[i][j] = '.';
        }
        grid->grid[i][size] = '\0';
    }
    
    return 0;
}

void free_grid(grid_t *grid)
{
    int i;
    
    if (grid->grid) {
        for (i = 0; i < grid->size; i++) {
            free(grid->grid[i]);
        }
        free(grid->grid);
    }
}

int can_place_word(grid_t *grid, char *word, int row, int col, direction_t dir)
{
    int len = strlen(word);
    int i, new_row, new_col;
    
    for (i = 0; i < len; i++) {
        new_row = row + i * dir.dx;
        new_col = col + i * dir.dy;
        
        if (new_row < 0 || new_row >= grid->size ||
            new_col < 0 || new_col >= grid->size)
            return 0;
        
        if (grid->grid[new_row][new_col] != '.' && 
            grid->grid[new_row][new_col] != word[i])
            return 0;
    }
    
    return 1;
}

void place_word(grid_t *grid, char *word, int row, int col, direction_t dir)
{
    int len = strlen(word);
    int i, new_row, new_col;
    
    for (i = 0; i < len; i++) {
        new_row = row + i * dir.dx;
        new_col = col + i * dir.dy;
        grid->grid[new_row][new_col] = word[i];
    }
}

int try_place_word(grid_t *grid, char *word)
{
    int row, col, dir_idx;
    
    for (row = 0; row < grid->size; row++) {
        for (col = 0; col < grid->size; col++) {
            for (dir_idx = 0; dir_idx < 8; dir_idx++) {
                if (can_place_word(grid, word, row, col, directions[dir_idx])) {
                    place_word(grid, word, row, col, directions[dir_idx]);
                    return 1;
                }
            }
        }
    }
    
    return 0;
}

void fill_random_letters(grid_t *grid)
{
    int i, j;
    
    srand(time(NULL));
    
    for (i = 0; i < grid->size; i++) {
        for (j = 0; j < grid->size; j++) {
            if (grid->grid[i][j] == '.') {
                grid->grid[i][j] = 'a' + (rand() % 26);
            }
        }
    }
}

void print_grid(grid_t *grid)
{
    int i, j;
    
    // Top border
    for (i = 0; i < grid->size + 2; i++)
        printf("+");
    printf("\n");
    
    // Grid content
    for (i = 0; i < grid->size; i++) {
        printf("|");
        for (j = 0; j < grid->size; j++) {
            printf("%c", grid->grid[i][j]);
        }
        printf("|\n");
    }
    
    // Bottom border
    for (i = 0; i < grid->size + 2; i++)
        printf("+");
    printf("\n");
}

int parse_args(int argc, char **argv, char **filename, int *size)
{
    int i;
    
    *filename = NULL;
    *size = 8;
    
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            *filename = argv[i + 1];
            i++;
        } else if (strcmp(argv[i], "-s") == 0 && i + 1 < argc) {
            *size = atoi(argv[i + 1]);
            i++;
        } else {
            print_usage();
            return 84;
        }
    }
    
    if (!*filename) {
        print_usage();
        return 84;
    }
    
    return 0;
}

int main(int argc, char **argv)
{
    dictionary_t dict;
    grid_t grid;
    char *filename;
    int size;
    int i;
    
    if (parse_args(argc, argv, &filename, &size) != 0)
        return 84;
    
    if (load_dictionary(filename, &dict) != 0)
        return 84;
    
    if (dict.word_count == 0) {
        free_dictionary(&dict);
        return 84;
    }
    
    // Check if grid size is sufficient for any word
    int min_size_needed = 0;
    for (i = 0; i < dict.word_count; i++) {
        int word_len = strlen(dict.words[i]);
        if (word_len > min_size_needed)
            min_size_needed = word_len;
    }
    
    if (size < min_size_needed) {
        free_dictionary(&dict);
        return 84;
    }
    
    if (init_grid(&grid, size) != 0) {
        free_dictionary(&dict);
        return 84;
    }
    
    // Try to place words (simple greedy approach)
    for (i = 0; i < dict.word_count; i++) {
        if (try_place_word(&grid, dict.words[i])) {
            grid.words_placed++;
        }
    }
    
    // Fill remaining spaces with random letters
    fill_random_letters(&grid);
    
    // Print results
    printf("%d/%d words inserted in the grid.\n", grid.words_placed, dict.word_count);
    print_grid(&grid);
    
    free_dictionary(&dict);
    free_grid(&grid);
    
    return 0;
}
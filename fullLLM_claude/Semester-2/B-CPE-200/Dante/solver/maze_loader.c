#include "solver.h"

static int get_file_size(FILE *file)
{
    int size;
    
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

static char *read_file_content(const char *filename)
{
    FILE *file = fopen(filename, "r");
    char *content;
    int size;
    
    if (!file)
        return NULL;
    
    size = get_file_size(file);
    if (size <= 0) {
        fclose(file);
        return NULL;
    }
    
    content = malloc(size + 1);
    if (!content) {
        fclose(file);
        return NULL;
    }
    
    if ((int)fread(content, 1, size, file) != size) {
        free(content);
        fclose(file);
        return NULL;
    }
    
    content[size] = '\0';
    fclose(file);
    return content;
}

static int count_lines(const char *content)
{
    int count = 0;
    int i;
    
    for (i = 0; content[i]; i++) {
        if (content[i] == '\n')
            count++;
    }
    if (i > 0 && content[i - 1] != '\n')
        count++;
    return count;
}

static int get_line_width(const char *line)
{
    int width = 0;
    
    while (line[width] && line[width] != '\n')
        width++;
    return width;
}

maze_t *load_maze(const char *filename)
{
    char *content = read_file_content(filename);
    maze_t *maze;
    int i, j, line_start, line_end;
    
    if (!content)
        return NULL;
    
    maze = malloc(sizeof(maze_t));
    if (!maze) {
        free(content);
        return NULL;
    }
    
    maze->height = count_lines(content);
    if (maze->height == 0) {
        free(content);
        free(maze);
        return NULL;
    }
    
    maze->width = get_line_width(content);
    
    maze->grid = malloc(sizeof(char *) * maze->height);
    if (!maze->grid) {
        free(content);
        free(maze);
        return NULL;
    }
    
    line_start = 0;
    for (i = 0; i < maze->height; i++) {
        line_end = line_start;
        while (content[line_end] && content[line_end] != '\n')
            line_end++;
        
        maze->grid[i] = malloc(maze->width + 1);
        if (!maze->grid[i]) {
            for (j = 0; j < i; j++)
                free(maze->grid[j]);
            free(maze->grid);
            free(maze);
            free(content);
            return NULL;
        }
        
        for (j = 0; j < maze->width && line_start + j < line_end; j++) {
            maze->grid[i][j] = content[line_start + j];
        }
        for (; j < maze->width; j++) {
            maze->grid[i][j] = 'X';
        }
        maze->grid[i][maze->width] = '\0';
        
        line_start = line_end + 1;
    }
    
    free(content);
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
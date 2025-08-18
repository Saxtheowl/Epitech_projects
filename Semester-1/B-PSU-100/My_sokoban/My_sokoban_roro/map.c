#include "my_sokoban.h"

static int get_map_dimensions(FILE *file, int *width, int *height)
{
    char *line = NULL;
    size_t len = 0;
    int max_width = 0;
    int h = 0;
    
    while (getline(&line, &len, file) != -1) {
        int w = my_strlen(line);
        if (w > 0 && line[w - 1] == '\n') {
            w--;
        }
        if (w > max_width)
            max_width = w;
        h++;
    }
    
    free(line);
    *width = max_width;
    *height = h;
    rewind(file);
    
    return (max_width > 0 && h > 0) ? 0 : -1;
}

static char **allocate_grid(int width, int height)
{
    char **grid;
    int i;
    
    grid = malloc(sizeof(char*) * height);
    if (!grid)
        return NULL;
    
    for (i = 0; i < height; i++) {
        grid[i] = malloc(sizeof(char) * (width + 1));
        if (!grid[i]) {
            while (--i >= 0)
                free(grid[i]);
            free(grid);
            return NULL;
        }
        memset(grid[i], ' ', width);
        grid[i][width] = '\0';
    }
    
    return grid;
}

static void fill_grid(FILE *file, char **grid, int width, int height)
{
    char *line = NULL;
    size_t len = 0;
    int row = 0;
    
    while (getline(&line, &len, file) != -1 && row < height) {
        int w = my_strlen(line);
        if (w > 0 && line[w - 1] == '\n') {
            line[w - 1] = '\0';
            w--;
        }
        
        for (int col = 0; col < width && col < w; col++) {
            grid[row][col] = line[col];
        }
        row++;
    }
    
    free(line);
}

static position_t find_player(map_t *map)
{
    position_t pos = {-1, -1};
    
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            if (map->grid[y][x] == PLAYER) {
                pos.x = x;
                pos.y = y;
                return pos;
            }
        }
    }
    
    return pos;
}

map_t *load_map(char *filename)
{
    FILE *file;
    map_t *map;
    
    if (!filename)
        return NULL;
    
    file = fopen(filename, "r");
    if (!file)
        return NULL;
    
    map = malloc(sizeof(map_t));
    if (!map) {
        fclose(file);
        return NULL;
    }
    
    if (get_map_dimensions(file, &map->width, &map->height) != 0) {
        free(map);
        fclose(file);
        return NULL;
    }
    
    map->grid = allocate_grid(map->width, map->height);
    map->original = allocate_grid(map->width, map->height);
    
    if (!map->grid || !map->original) {
        free_map(map);
        fclose(file);
        return NULL;
    }
    
    fill_grid(file, map->grid, map->width, map->height);
    fclose(file);
    
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            map->original[y][x] = map->grid[y][x];
        }
    }
    
    map->player = find_player(map);
    map->boxes_count = count_char(map, BOX);
    map->storage_count = count_char(map, STORAGE);
    
    return map;
}

void free_map(map_t *map)
{
    if (!map)
        return;
    
    if (map->grid) {
        for (int i = 0; i < map->height; i++) {
            free(map->grid[i]);
        }
        free(map->grid);
    }
    
    if (map->original) {
        for (int i = 0; i < map->height; i++) {
            free(map->original[i]);
        }
        free(map->original);
    }
    
    free(map);
}

int validate_map(map_t *map)
{
    int player_count = 0;
    
    if (!map || !map->grid)
        return -1;
    
    if (map->player.x == -1 || map->player.y == -1)
        return -1;
    
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            char c = map->grid[y][x];
            if (c != WALL && c != PLAYER && c != BOX && c != STORAGE && c != SPACE) {
                return -1;
            }
            if (c == PLAYER)
                player_count++;
        }
    }
    
    if (player_count != 1)
        return -1;
    
    if (map->boxes_count != map->storage_count)
        return -1;
    
    return 0;
}

int count_char(map_t *map, char c)
{
    int count = 0;
    
    if (!map || !map->grid)
        return 0;
    
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            if (map->grid[y][x] == c)
                count++;
        }
    }
    
    return count;
}
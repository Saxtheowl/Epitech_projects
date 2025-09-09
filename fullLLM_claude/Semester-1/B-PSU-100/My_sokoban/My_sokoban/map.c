#include "sokoban.h"

static char *read_file(char const *filepath)
{
    int fd;
    struct stat st;
    char *buffer;
    int bytes_read;
    
    fd = open(filepath, O_RDONLY);
    if (fd == -1)
        return NULL;
    
    if (fstat(fd, &st) == -1) {
        close(fd);
        return NULL;
    }
    
    buffer = malloc(st.st_size + 1);
    if (!buffer) {
        close(fd);
        return NULL;
    }
    
    bytes_read = read(fd, buffer, st.st_size);
    if (bytes_read == -1) {
        free(buffer);
        close(fd);
        return NULL;
    }
    
    buffer[bytes_read] = '\0';
    close(fd);
    
    return buffer;
}

static int count_lines(char const *str)
{
    int lines = 0;
    int i = 0;
    
    while (str[i]) {
        if (str[i] == '\n')
            lines++;
        i++;
    }
    
    if (i > 0 && str[i - 1] != '\n')
        lines++;
    
    return lines;
}

static int get_line_width(char const *str, int line)
{
    int current_line = 0;
    int i = 0;
    int width = 0;
    
    while (str[i] && current_line < line) {
        if (str[i] == '\n')
            current_line++;
        i++;
    }
    
    while (str[i] && str[i] != '\n') {
        width++;
        i++;
    }
    
    return width;
}

static int get_max_width(char const *str)
{
    int lines = count_lines(str);
    int max_width = 0;
    int i;
    
    for (i = 0; i < lines; i++) {
        int width = get_line_width(str, i);
        if (width > max_width)
            max_width = width;
    }
    
    return max_width;
}

sokoban_map_t *make_map_from_string(char const *str)
{
    sokoban_map_t *map;
    int i, j, k = 0;
    
    if (!str)
        return NULL;
    
    map = malloc(sizeof(sokoban_map_t));
    if (!map)
        return NULL;
    
    map->height = count_lines(str);
    map->width = get_max_width(str);
    map->boxes_count = 0;
    map->storage_count = 0;
    map->player_pos.x = -1;
    map->player_pos.y = -1;
    
    map->map = malloc(sizeof(char *) * map->height);
    if (!map->map) {
        free(map);
        return NULL;
    }
    
    for (i = 0; i < map->height; i++) {
        map->map[i] = malloc(sizeof(char) * (map->width + 1));
        if (!map->map[i]) {
            for (j = 0; j < i; j++)
                free(map->map[j]);
            free(map->map);
            free(map);
            return NULL;
        }
        
        for (j = 0; j < map->width; j++) {
            if (str[k] && str[k] != '\n') {
                map->map[i][j] = str[k];
                if (str[k] == PLAYER) {
                    map->player_pos.x = j;
                    map->player_pos.y = i;
                } else if (str[k] == BOX) {
                    map->boxes_count++;
                } else if (str[k] == STORAGE) {
                    map->storage_count++;
                }
                k++;
            } else {
                map->map[i][j] = EMPTY;
            }
        }
        map->map[i][j] = '\0';
        
        if (str[k] == '\n')
            k++;
    }
    
    return map;
}

sokoban_map_t *load_map(char const *filepath)
{
    char *content;
    sokoban_map_t *map;
    
    content = read_file(filepath);
    if (!content)
        return NULL;
    
    map = make_map_from_string(content);
    free(content);
    
    return map;
}

void free_map(sokoban_map_t *map)
{
    int i;
    
    if (!map)
        return;
    
    if (map->map) {
        for (i = 0; i < map->height; i++) {
            if (map->map[i])
                free(map->map[i]);
        }
        free(map->map);
    }
    
    free(map);
}

position_t *get_player_position(sokoban_map_t *map)
{
    position_t *pos;
    
    if (!map || map->player_pos.x == -1 || map->player_pos.y == -1)
        return NULL;
    
    pos = malloc(sizeof(position_t));
    if (!pos)
        return NULL;
    
    pos->x = map->player_pos.x;
    pos->y = map->player_pos.y;
    
    return pos;
}
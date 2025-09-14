#include "tetris.h"

static int load_tetrimino_file(char *filename, tetrimino_t *tetrimino)
{
    FILE *file = fopen(filename, "r");
    char line[256];
    
    if (!file) {
        tetrimino->valid = 0;
        return -1;
    }
    
    // Extract name from filename
    char *name_start = strrchr(filename, '/');
    if (name_start)
        name_start++;
    else
        name_start = filename;
    
    char *dot = strrchr(name_start, '.');
    if (dot)
        *dot = '\0';
    
    strncpy(tetrimino->name, name_start, MAX_NAME_LEN - 1);
    tetrimino->name[MAX_NAME_LEN - 1] = '\0';
    
    // Read first line: width height color
    if (!fgets(line, sizeof(line), file)) {
        fclose(file);
        tetrimino->valid = 0;
        return -1;
    }
    
    if (sscanf(line, "%d %d %d", &tetrimino->width, &tetrimino->height, &tetrimino->color) != 3) {
        fclose(file);
        tetrimino->valid = 0;
        return -1;
    }
    
    if (tetrimino->width <= 0 || tetrimino->height <= 0 || 
        tetrimino->width > MAX_SHAPE_SIZE || tetrimino->height > MAX_SHAPE_SIZE) {
        fclose(file);
        tetrimino->valid = 0;
        return -1;
    }
    
    // Initialize shape
    for (int i = 0; i < MAX_SHAPE_SIZE; i++) {
        for (int j = 0; j < MAX_SHAPE_SIZE; j++) {
            tetrimino->shape[i][j] = ' ';
        }
    }
    
    // Read shape
    for (int i = 0; i < tetrimino->height; i++) {
        if (!fgets(line, sizeof(line), file)) {
            fclose(file);
            tetrimino->valid = 0;
            return -1;
        }
        
        // Remove newline
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';
        
        for (int j = 0; j < tetrimino->width && j < (int)strlen(line); j++) {
            tetrimino->shape[i][j] = line[j];
        }
    }
    
    fclose(file);
    tetrimino->valid = 1;
    return 0;
}

static int compare_tetriminos(const void *a, const void *b)
{
    tetrimino_t *ta = (tetrimino_t *)a;
    tetrimino_t *tb = (tetrimino_t *)b;
    return strcmp(ta->name, tb->name);
}

int load_tetriminos(tetrimino_t *tetriminos, int *count)
{
    DIR *dir = opendir("tetriminos");
    struct dirent *entry;
    char filepath[512];
    int loaded = 0;
    
    if (!dir) {
        fprintf(stderr, "Error: Cannot open tetriminos directory\n");
        return -1;
    }
    
    while ((entry = readdir(dir)) != NULL && loaded < MAX_TETRIMINOS) {
        if (strstr(entry->d_name, ".tetrimino")) {
            snprintf(filepath, sizeof(filepath), "tetriminos/%s", entry->d_name);
            load_tetrimino_file(filepath, &tetriminos[loaded]);
            loaded++;
        }
    }
    
    closedir(dir);
    
    // Sort tetriminos alphabetically
    qsort(tetriminos, loaded, sizeof(tetrimino_t), compare_tetriminos);
    
    *count = loaded;
    return loaded > 0 ? 0 : -1;
}

void print_debug_info(options_t *options, tetrimino_t *tetriminos, int count)
{
    printf("*** DEBUG MODE ***\n");
    
    // Print key bindings
    if (options->key_left == KEY_LEFT)
        printf("Key Left : ^EOD\n");
    else
        printf("Key Left : %c\n", options->key_left);
    
    if (options->key_right == KEY_RIGHT)
        printf("Key Right : ^EOC\n");
    else
        printf("Key Right : %c\n", options->key_right);
    
    if (options->key_turn == KEY_UP)
        printf("Key Turn : ^EOA\n");
    else if (options->key_turn == ' ')
        printf("Key Turn : (space)\n");
    else
        printf("Key Turn : %c\n", options->key_turn);
    
    if (options->key_drop == KEY_DOWN)
        printf("Key Drop : ^EOB\n");
    else
        printf("Key Drop : %c\n", options->key_drop);
    
    printf("Key Quit : %c\n", options->key_quit);
    
    if (options->key_pause == ' ')
        printf("Key Pause : (space)\n");
    else
        printf("Key Pause : %c\n", options->key_pause);
    
    printf("Next : %s\n", options->without_next ? "No" : "Yes");
    printf("Level : %d\n", options->level);
    printf("Size : %d*%d\n", options->rows, options->cols);
    printf("Tetriminos : %d\n", count);
    
    // Print tetriminos info
    for (int i = 0; i < count; i++) {
        if (!tetriminos[i].valid) {
            printf("Tetriminos : Name %s : Error\n", tetriminos[i].name);
            continue;
        }
        
        printf("Tetriminos : Name %s : Size %d*%d : Color %d :\n",
               tetriminos[i].name, tetriminos[i].width, tetriminos[i].height, tetriminos[i].color);
        
        for (int row = 0; row < tetriminos[i].height; row++) {
            for (int col = 0; col < tetriminos[i].width; col++) {
                putchar(tetriminos[i].shape[row][col]);
            }
            putchar('\n');
        }
    }
}
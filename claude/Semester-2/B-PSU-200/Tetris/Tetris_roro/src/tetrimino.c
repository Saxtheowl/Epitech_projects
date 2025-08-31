/*
** EPITECH PROJECT, 2024
** Tetris
** File description:
** Tetrimino loading and management
*/

#include "../include/tetris.h"

int load_tetriminos(game_t *game)
{
    DIR *dir;
    struct dirent *entry;
    char filepath[MAX_PATH_LENGTH];
    char *extension;

    game->tetrimino_count = 0;

    dir = opendir("./tetriminos");
    if (!dir) {
        print_error("Cannot open tetriminos directory");
        return -1;
    }

    while ((entry = readdir(dir)) && game->tetrimino_count < MAX_TETRIMINOS) {
        if (entry->d_name[0] == '.')
            continue;

        extension = strrchr(entry->d_name, '.');
        if (!extension || my_strcmp(extension, ".tetrimino") != 0)
            continue;

        snprintf(filepath, sizeof(filepath), "./tetriminos/%s", entry->d_name);
        
        strncpy(game->tetriminos[game->tetrimino_count].name, entry->d_name, MAX_NAME_LENGTH - 1);
        char *dot = strrchr(game->tetriminos[game->tetrimino_count].name, '.');
        if (dot) *dot = '\0';

        if (load_tetrimino_file(filepath, &game->tetriminos[game->tetrimino_count]) == 0) {
            game->tetriminos[game->tetrimino_count].valid = 1;
        } else {
            game->tetriminos[game->tetrimino_count].valid = 0;
        }
        
        game->tetrimino_count++;
    }

    closedir(dir);

    for (int i = 0; i < game->tetrimino_count - 1; i++) {
        for (int j = i + 1; j < game->tetrimino_count; j++) {
            if (my_strcmp(game->tetriminos[i].name, game->tetriminos[j].name) > 0) {
                tetrimino_t temp = game->tetriminos[i];
                game->tetriminos[i] = game->tetriminos[j];
                game->tetriminos[j] = temp;
            }
        }
    }

    return game->tetrimino_count > 0 ? 0 : -1;
}

int load_tetrimino_file(const char *filepath, tetrimino_t *tetrimino)
{
    FILE *file;
    char line[256];
    int i;

    file = fopen(filepath, "r");
    if (!file)
        return -1;

    if (!fgets(line, sizeof(line), file)) {
        fclose(file);
        return -1;
    }

    if (sscanf(line, "%d %d %d", &tetrimino->width, &tetrimino->height, &tetrimino->color) != 3) {
        fclose(file);
        return -1;
    }

    if (tetrimino->width <= 0 || tetrimino->height <= 0 || 
        tetrimino->width > 10 || tetrimino->height > 10) {
        fclose(file);
        return -1;
    }

    tetrimino->shape = malloc(tetrimino->height * sizeof(char *));
    if (!tetrimino->shape) {
        fclose(file);
        return -1;
    }

    for (i = 0; i < tetrimino->height; i++) {
        tetrimino->shape[i] = malloc(tetrimino->width + 1);
        if (!tetrimino->shape[i]) {
            for (int j = 0; j < i; j++) {
                free(tetrimino->shape[j]);
            }
            free(tetrimino->shape);
            fclose(file);
            return -1;
        }

        if (!fgets(line, sizeof(line), file)) {
            for (int j = 0; j <= i; j++) {
                free(tetrimino->shape[j]);
            }
            free(tetrimino->shape);
            fclose(file);
            return -1;
        }

        if (line[my_strlen(line) - 1] == '\n') {
            line[my_strlen(line) - 1] = '\0';
        }

        if (my_strlen(line) < tetrimino->width) {
            for (int k = my_strlen(line); k < tetrimino->width; k++) {
                line[k] = ' ';
            }
            line[tetrimino->width] = '\0';
        } else if (my_strlen(line) > tetrimino->width) {
            line[tetrimino->width] = '\0';
        }

        strcpy(tetrimino->shape[i], line);
    }

    fclose(file);
    return 0;
}

void free_tetrimino(tetrimino_t *tetrimino)
{
    if (tetrimino->shape) {
        for (int i = 0; i < tetrimino->height; i++) {
            free(tetrimino->shape[i]);
        }
        free(tetrimino->shape);
        tetrimino->shape = NULL;
    }
}

tetrimino_t *get_random_tetrimino(game_t *game)
{
    int valid_count = 0;
    int valid_indices[MAX_TETRIMINOS];
    int random_index;

    for (int i = 0; i < game->tetrimino_count; i++) {
        if (game->tetriminos[i].valid) {
            valid_indices[valid_count++] = i;
        }
    }

    if (valid_count == 0)
        return NULL;

    random_index = rand() % valid_count;
    return &game->tetriminos[valid_indices[random_index]];
}

tetrimino_t *copy_tetrimino(tetrimino_t *original)
{
    tetrimino_t *copy;
    int i;

    if (!original)
        return NULL;

    copy = malloc(sizeof(tetrimino_t));
    if (!copy)
        return NULL;

    *copy = *original;
    
    copy->shape = malloc(copy->height * sizeof(char *));
    if (!copy->shape) {
        free(copy);
        return NULL;
    }

    for (i = 0; i < copy->height; i++) {
        copy->shape[i] = my_strdup(original->shape[i]);
        if (!copy->shape[i]) {
            for (int j = 0; j < i; j++) {
                free(copy->shape[j]);
            }
            free(copy->shape);
            free(copy);
            return NULL;
        }
    }

    return copy;
}

tetrimino_t *rotate_tetrimino(tetrimino_t *tetrimino, int rotation)
{
    tetrimino_t *rotated;
    int i, j;

    rotation = rotation % 4;
    if (rotation == 0)
        return copy_tetrimino(tetrimino);

    rotated = malloc(sizeof(tetrimino_t));
    if (!rotated)
        return NULL;

    *rotated = *tetrimino;

    if (rotation == 1 || rotation == 3) {
        rotated->width = tetrimino->height;
        rotated->height = tetrimino->width;
    }

    rotated->shape = malloc(rotated->height * sizeof(char *));
    if (!rotated->shape) {
        free(rotated);
        return NULL;
    }

    for (i = 0; i < rotated->height; i++) {
        rotated->shape[i] = malloc(rotated->width + 1);
        if (!rotated->shape[i]) {
            for (int k = 0; k < i; k++) {
                free(rotated->shape[k]);
            }
            free(rotated->shape);
            free(rotated);
            return NULL;
        }
        rotated->shape[i][rotated->width] = '\0';
    }

    for (i = 0; i < tetrimino->height; i++) {
        for (j = 0; j < tetrimino->width; j++) {
            int new_i, new_j;
            
            switch (rotation) {
            case 1:
                new_i = j;
                new_j = tetrimino->height - 1 - i;
                break;
            case 2:
                new_i = tetrimino->height - 1 - i;
                new_j = tetrimino->width - 1 - j;
                break;
            case 3:
                new_i = tetrimino->width - 1 - j;
                new_j = i;
                break;
            default:
                new_i = i;
                new_j = j;
                break;
            }
            
            if (new_i >= 0 && new_i < rotated->height && 
                new_j >= 0 && new_j < rotated->width) {
                rotated->shape[new_i][new_j] = tetrimino->shape[i][j];
            }
        }
    }

    for (i = 0; i < rotated->height; i++) {
        for (j = 0; j < rotated->width; j++) {
            if (rotated->shape[i][j] == '\0') {
                rotated->shape[i][j] = ' ';
            }
        }
    }

    return rotated;
}
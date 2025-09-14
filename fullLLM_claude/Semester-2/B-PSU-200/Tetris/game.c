#include "tetris.h"

int init_game(game_t *game, options_t *options)
{
    game->rows = options->rows;
    game->cols = options->cols;
    game->score = 0;
    game->high_score = 1400; // Default high score from example
    game->lines_cleared = 0;
    game->level = options->level;
    game->start_time = time(NULL);
    game->paused = 0;
    game->game_over = 0;
    
    // Allocate grid
    game->grid = malloc(game->rows * sizeof(char *));
    if (!game->grid)
        return -1;
    
    for (int i = 0; i < game->rows; i++) {
        game->grid[i] = calloc(game->cols + 1, sizeof(char));
        if (!game->grid[i])
            return -1;
        for (int j = 0; j < game->cols; j++)
            game->grid[i][j] = ' ';
        game->grid[i][game->cols] = '\0';
    }
    
    // Initialize random seed
    srand(time(NULL));
    
    // Initialize current and next pieces
    game->current_piece.tetrimino = get_random_tetrimino(game->tetriminos, game->tetrimino_count);
    game->current_piece.x = game->cols / 2 - game->current_piece.tetrimino->width / 2;
    game->current_piece.y = 0;
    game->current_piece.rotation = 0;
    
    game->next_piece.tetrimino = get_random_tetrimino(game->tetriminos, game->tetrimino_count);
    game->next_piece.x = 0;
    game->next_piece.y = 0;
    game->next_piece.rotation = 0;
    
    return 0;
}

void cleanup(game_t *game)
{
    if (game->grid) {
        for (int i = 0; i < game->rows; i++) {
            if (game->grid[i])
                free(game->grid[i]);
        }
        free(game->grid);
    }
}

tetrimino_t *get_random_tetrimino(tetrimino_t *tetriminos, int count)
{
    int valid_count = 0;
    
    // Count valid tetriminos
    for (int i = 0; i < count; i++) {
        if (tetriminos[i].valid)
            valid_count++;
    }
    
    if (valid_count == 0)
        return NULL;
    
    int random_index = rand() % valid_count;
    int current = 0;
    
    // Find the random valid tetrimino
    for (int i = 0; i < count; i++) {
        if (tetriminos[i].valid) {
            if (current == random_index)
                return &tetriminos[i];
            current++;
        }
    }
    
    return NULL;
}

int can_place_piece(game_t *game, piece_t *piece, int x, int y)
{
    if (!piece->tetrimino || !piece->tetrimino->valid)
        return 0;
    
    for (int row = 0; row < piece->tetrimino->height; row++) {
        for (int col = 0; col < piece->tetrimino->width; col++) {
            if (piece->tetrimino->shape[row][col] == '*') {
                int grid_x = x + col;
                int grid_y = y + row;
                
                // Check bounds
                if (grid_x < 0 || grid_x >= game->cols || 
                    grid_y < 0 || grid_y >= game->rows)
                    return 0;
                
                // Check collision with existing pieces
                if (game->grid[grid_y][grid_x] != ' ')
                    return 0;
            }
        }
    }
    
    return 1;
}

int move_piece(game_t *game, int dx, int dy)
{
    int new_x = game->current_piece.x + dx;
    int new_y = game->current_piece.y + dy;
    
    if (can_place_piece(game, &game->current_piece, new_x, new_y)) {
        game->current_piece.x = new_x;
        game->current_piece.y = new_y;
        return 1;
    }
    
    return 0;
}

void rotate_tetrimino_shape(char shape[MAX_SHAPE_SIZE][MAX_SHAPE_SIZE], int size)
{
    char temp[MAX_SHAPE_SIZE][MAX_SHAPE_SIZE];
    
    // Copy to temp
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            temp[i][j] = shape[i][j];
        }
    }
    
    // Rotate: new[j][size-1-i] = old[i][j]
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            shape[j][size - 1 - i] = temp[i][j];
        }
    }
}

int rotate_piece(game_t *game)
{
    if (!game->current_piece.tetrimino || !game->current_piece.tetrimino->valid)
        return 0;
    
    // Create a copy of the tetrimino to test rotation
    tetrimino_t rotated = *game->current_piece.tetrimino;
    int size = (rotated.width > rotated.height) ? rotated.width : rotated.height;
    
    rotate_tetrimino_shape(rotated.shape, size);
    
    // Swap width and height for rotation
    int temp = rotated.width;
    rotated.width = rotated.height;
    rotated.height = temp;
    
    // Test if rotated piece can be placed
    piece_t test_piece = game->current_piece;
    test_piece.tetrimino = &rotated;
    
    if (can_place_piece(game, &test_piece, test_piece.x, test_piece.y)) {
        *game->current_piece.tetrimino = rotated;
        return 1;
    }
    
    return 0;
}

void place_piece(game_t *game)
{
    if (!game->current_piece.tetrimino || !game->current_piece.tetrimino->valid)
        return;
    
    for (int row = 0; row < game->current_piece.tetrimino->height; row++) {
        for (int col = 0; col < game->current_piece.tetrimino->width; col++) {
            if (game->current_piece.tetrimino->shape[row][col] == '*') {
                int grid_x = game->current_piece.x + col;
                int grid_y = game->current_piece.y + row;
                
                if (grid_x >= 0 && grid_x < game->cols && 
                    grid_y >= 0 && grid_y < game->rows) {
                    game->grid[grid_y][grid_x] = '*';
                }
            }
        }
    }
}

int check_lines(game_t *game)
{
    int lines_cleared = 0;
    
    for (int row = game->rows - 1; row >= 0; row--) {
        int full_line = 1;
        
        for (int col = 0; col < game->cols; col++) {
            if (game->grid[row][col] == ' ') {
                full_line = 0;
                break;
            }
        }
        
        if (full_line) {
            lines_cleared++;
            
            // Move all lines above down
            for (int r = row; r > 0; r--) {
                for (int c = 0; c < game->cols; c++) {
                    game->grid[r][c] = game->grid[r - 1][c];
                }
            }
            
            // Clear top line
            for (int c = 0; c < game->cols; c++) {
                game->grid[0][c] = ' ';
            }
            
            // Check the same row again
            row++;
        }
    }
    
    if (lines_cleared > 0) {
        game->lines_cleared += lines_cleared;
        game->level = 1 + game->lines_cleared / 10;
        game->score += lines_cleared * 100 * game->level;
        if (game->score > game->high_score)
            game->high_score = game->score;
    }
    
    return lines_cleared;
}

void spawn_next_piece(game_t *game)
{
    game->current_piece = game->next_piece;
    game->current_piece.x = game->cols / 2 - game->current_piece.tetrimino->width / 2;
    game->current_piece.y = 0;
    
    game->next_piece.tetrimino = get_random_tetrimino(game->tetriminos, game->tetrimino_count);
    
    // Check if game over
    if (!can_place_piece(game, &game->current_piece, game->current_piece.x, game->current_piece.y)) {
        game->game_over = 1;
    }
}
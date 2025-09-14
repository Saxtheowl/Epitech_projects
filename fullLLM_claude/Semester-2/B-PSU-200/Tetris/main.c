#include "tetris.h"

int main(int argc, char **argv)
{
    options_t options = {
        .key_left = KEY_LEFT,
        .key_right = KEY_RIGHT,
        .key_turn = KEY_UP,
        .key_drop = KEY_DOWN,
        .key_quit = 'q',
        .key_pause = ' ',
        .level = DEFAULT_LEVEL,
        .rows = DEFAULT_ROWS,
        .cols = DEFAULT_COLS,
        .without_next = 0,
        .debug = 0
    };
    
    game_t game;
    tetrimino_t tetriminos[MAX_TETRIMINOS];
    int tetrimino_count;
    
    if (parse_args(argc, argv, &options) != 0)
        return 84;
    
    if (load_tetriminos(tetriminos, &tetrimino_count) != 0) {
        fprintf(stderr, "Error loading tetriminos\n");
        return 84;
    }
    
    if (options.debug) {
        print_debug_info(&options, tetriminos, tetrimino_count);
        printf("Press any key to start Tetris\n");
        getchar();
    }
    
    // Copy tetriminos to game
    game.tetrimino_count = tetrimino_count;
    for (int i = 0; i < tetrimino_count; i++)
        game.tetriminos[i] = tetriminos[i];
    
    if (init_game(&game, &options) != 0) {
        fprintf(stderr, "Error: Terminal too small\n");
        return 84;
    }
    
    init_ncurses();
    
    int result = game_loop(&game, &options);
    
    cleanup(&game);
    endwin();
    
    return result;
}
#include "tetris.h"

static int get_fall_delay(int level)
{
    // Falling speed increases with level
    // Level 1: 1000ms, Level 2: 800ms, etc.
    int delay = 1200 - (level * 100);
    if (delay < 100)
        delay = 100;
    return delay;
}

int game_loop(game_t *game, options_t *options)
{
    int last_fall = 0;
    int fall_delay;
    int ch;
    
    while (!game->game_over) {
        fall_delay = get_fall_delay(game->level);
        
        // Handle input
        ch = getch();
        
        if (ch == options->key_quit) {
            break;
        }
        
        if (ch == options->key_pause) {
            game->paused = !game->paused;
        }
        
        if (!game->paused && !game->game_over) {
            if (ch == options->key_left) {
                move_piece(game, -1, 0);
            } else if (ch == options->key_right) {
                move_piece(game, 1, 0);
            } else if (ch == options->key_turn) {
                rotate_piece(game);
            } else if (ch == options->key_drop) {
                // Drop piece all the way down
                while (move_piece(game, 0, 1)) {
                    // Continue dropping
                }
                // Place the piece immediately
                place_piece(game);
                check_lines(game);
                spawn_next_piece(game);
                last_fall = 0; // Reset fall timer
            }
            
            // Handle automatic falling
            int current_time = (int)(time(NULL) * 1000) % 1000000;
            if (current_time - last_fall > fall_delay || last_fall == 0) {
                if (!move_piece(game, 0, 1)) {
                    // Piece can't move down, place it
                    place_piece(game);
                    check_lines(game);
                    spawn_next_piece(game);
                }
                last_fall = current_time;
            }
        }
        
        draw_game(game, options);
        
        // Small delay to prevent excessive CPU usage
        usleep(50000); // 50ms
    }
    
    // Game over screen
    if (game->game_over) {
        draw_game(game, options);
        mvprintw(LINES/2, (COLS-20)/2, "GAME OVER!");
        mvprintw(LINES/2 + 1, (COLS-25)/2, "Press 'q' to quit");
        refresh();
        
        // Wait for quit key
        while ((ch = getch()) != options->key_quit) {
            usleep(100000);
        }
    }
    
    return 0;
}
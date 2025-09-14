/*
** EPITECH PROJECT, 2024
** Gomoku AI
** File description:
** Pattern recognition for threat detection and tactical analysis
*/

#include "gomoku.h"

static int count_pattern_in_direction(const game_board_t *board, int x, int y, 
                                     int dx, int dy, player_t player, int length)
{
    int count = 0;
    int open_ends = 0;
    int nx, ny;
    int start_x = x, start_y = y;
    
    // Find the start of the pattern
    while (start_x - dx >= 0 && start_x - dx < BOARD_SIZE && 
           start_y - dy >= 0 && start_y - dy < BOARD_SIZE &&
           board->board[start_y - dy][start_x - dx] == (int)player) {
        start_x -= dx;
        start_y -= dy;
    }
    
    // Count consecutive stones
    nx = start_x;
    ny = start_y;
    while (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE && 
           board->board[ny][nx] == (int)player) {
        count++;
        nx += dx;
        ny += dy;
    }
    
    // Check for open ends
    if (start_x - dx >= 0 && start_x - dx < BOARD_SIZE && 
        start_y - dy >= 0 && start_y - dy < BOARD_SIZE &&
        board->board[start_y - dy][start_x - dx] == EMPTY) {
        open_ends++;
    }
    
    if (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE &&
        board->board[ny][nx] == EMPTY) {
        open_ends++;
    }
    
    if (count == length) {
        if (open_ends == 2) {
            return 2; // Open pattern
        } else if (open_ends == 1) {
            return 1; // Semi-open pattern
        }
    }
    
    return 0;
}

static void analyze_position_patterns(const game_board_t *board, int x, int y, 
                                    player_t player, pattern_eval_t *patterns)
{
    int directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};
    int i, j;
    
    for (i = 0; i < 4; i++) {
        int dx = directions[i][0];
        int dy = directions[i][1];
        
        // Check for different pattern lengths
        for (j = 2; j <= 5; j++) {
            int pattern_type = count_pattern_in_direction(board, x, y, dx, dy, player, j);
            
            if (pattern_type > 0) {
                if (j == 5) {
                    patterns->count[PATTERN_FIVE]++;
                } else if (j == 4) {
                    if (pattern_type == 2) {
                        patterns->count[PATTERN_OPEN_FOUR]++;
                    } else {
                        patterns->count[PATTERN_FOUR]++;
                    }
                } else if (j == 3) {
                    if (pattern_type == 2) {
                        patterns->count[PATTERN_OPEN_THREE]++;
                    } else {
                        patterns->count[PATTERN_THREE]++;
                    }
                } else if (j == 2) {
                    if (pattern_type == 2) {
                        patterns->count[PATTERN_OPEN_TWO]++;
                    } else {
                        patterns->count[PATTERN_TWO]++;
                    }
                }
            }
        }
    }
}

void analyze_patterns(const game_board_t *board, pattern_eval_t *ai_patterns, pattern_eval_t *opp_patterns)
{
    int i, j, k;
    
    // Initialize pattern counts
    for (k = 0; k < PATTERN_COUNT; k++) {
        ai_patterns->count[k] = 0;
        opp_patterns->count[k] = 0;
    }
    
    // Analyze all positions on the board
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (board->board[i][j] == (int)PLAYER_AI) {
                analyze_position_patterns(board, j, i, PLAYER_AI, ai_patterns);
            } else if (board->board[i][j] == (int)PLAYER_OPPONENT) {
                analyze_position_patterns(board, j, i, PLAYER_OPPONENT, opp_patterns);
            }
        }
    }
    
    // Calculate threat levels
    ai_patterns->threat_level = 0;
    opp_patterns->threat_level = 0;
    
    if (ai_patterns->count[PATTERN_FIVE] > 0) {
        ai_patterns->threat_level = 1000000;
    } else if (ai_patterns->count[PATTERN_OPEN_FOUR] > 0) {
        ai_patterns->threat_level = 100000;
    } else if (ai_patterns->count[PATTERN_FOUR] > 0) {
        ai_patterns->threat_level = 10000;
    }
    
    if (opp_patterns->count[PATTERN_FIVE] > 0) {
        opp_patterns->threat_level = 1000000;
    } else if (opp_patterns->count[PATTERN_OPEN_FOUR] > 0) {
        opp_patterns->threat_level = 100000;
    } else if (opp_patterns->count[PATTERN_FOUR] > 0) {
        opp_patterns->threat_level = 10000;
    }
}

int detect_threat(const game_board_t *board, int x, int y, player_t player)
{
    game_board_t temp_board;
    pattern_eval_t patterns;
    int k;
    
    copy_board(&temp_board, board);
    make_move(&temp_board, x, y, player);
    
    // Initialize pattern count
    for (k = 0; k < PATTERN_COUNT; k++) {
        patterns.count[k] = 0;
    }
    
    analyze_position_patterns(&temp_board, x, y, player, &patterns);
    
    if (patterns.count[PATTERN_FIVE] > 0) {
        return 1000000; // Winning move
    }
    if (patterns.count[PATTERN_OPEN_FOUR] > 0) {
        return 100000; // Immediate threat
    }
    if (patterns.count[PATTERN_FOUR] > 0) {
        return 10000; // Strong threat
    }
    if (patterns.count[PATTERN_OPEN_THREE] > 0) {
        return 1000; // Medium threat
    }
    
    return 0;
}

int is_winning_move(const game_board_t *board, int x, int y, player_t player)
{
    game_board_t temp_board;
    
    copy_board(&temp_board, board);
    make_move(&temp_board, x, y, player);
    
    return check_win(&temp_board, x, y, player);
}

int is_blocking_move(const game_board_t *board, int x, int y, player_t opponent)
{
    return is_winning_move(board, x, y, opponent);
}
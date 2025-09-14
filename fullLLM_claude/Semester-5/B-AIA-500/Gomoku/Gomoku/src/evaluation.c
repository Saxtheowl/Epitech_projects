/*
** EPITECH PROJECT, 2024
** Gomoku AI
** File description:
** Board evaluation and position scoring
*/

#include "gomoku.h"

int pattern_score(pattern_type_t type)
{
    static const int scores[PATTERN_COUNT] = {
        1000000,  // PATTERN_FIVE
        100000,   // PATTERN_OPEN_FOUR
        10000,    // PATTERN_FOUR
        1000,     // PATTERN_OPEN_THREE
        100,      // PATTERN_THREE
        10,       // PATTERN_OPEN_TWO
        5,        // PATTERN_TWO
        1         // PATTERN_ONE
    };
    
    if (type >= 0 && type < PATTERN_COUNT) {
        return scores[type];
    }
    return 0;
}

static int evaluate_patterns(const pattern_eval_t *patterns)
{
    int score = 0;
    int i;
    
    for (i = 0; i < PATTERN_COUNT; i++) {
        score += patterns->count[i] * pattern_score(i);
    }
    
    return score;
}

static int evaluate_center_control(const game_board_t *board)
{
    int center = BOARD_SIZE / 2;
    int score = 0;
    int i, j;
    
    // Give bonus for controlling center positions
    for (i = center - 2; i <= center + 2; i++) {
        for (j = center - 2; j <= center + 2; j++) {
            if (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE) {
                int distance = abs(i - center) + abs(j - center);
                int bonus = 5 - distance;
                
                if (board->board[i][j] == (int)PLAYER_AI) {
                    score += bonus;
                } else if (board->board[i][j] == (int)PLAYER_OPPONENT) {
                    score -= bonus;
                }
            }
        }
    }
    
    return score;
}

static int evaluate_connectivity(const game_board_t *board)
{
    int score = 0;
    int i, j, k;
    int directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};
    
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (board->board[i][j] != (int)EMPTY) {
                player_t player = board->board[i][j];
                
                // Check connectivity in all directions
                for (k = 0; k < 4; k++) {
                    int dx = directions[k][0];
                    int dy = directions[k][1];
                    int count = 1;
                    
                    // Count consecutive stones in positive direction
                    int nx = j + dx;
                    int ny = i + dy;
                    while (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE && 
                           board->board[ny][nx] == (int)player) {
                        count++;
                        nx += dx;
                        ny += dy;
                    }
                    
                    // Award points for connectivity
                    int connectivity_bonus = count * count;
                    if (player == PLAYER_AI) {
                        score += connectivity_bonus;
                    } else {
                        score -= connectivity_bonus;
                    }
                }
            }
        }
    }
    
    return score;
}

int evaluate_board(const game_board_t *board)
{
    pattern_eval_t ai_patterns, opp_patterns;
    int score = 0;
    
    // Check for immediate win/loss conditions
    if (board->move_count > 0) {
        if (check_win(board, board->last_move.x, board->last_move.y, PLAYER_AI)) {
            return 1000000;
        }
        if (check_win(board, board->last_move.x, board->last_move.y, PLAYER_OPPONENT)) {
            return -1000000;
        }
    }
    
    // Analyze patterns
    analyze_patterns(board, &ai_patterns, &opp_patterns);
    
    // Calculate pattern-based score
    score += evaluate_patterns(&ai_patterns);
    score -= evaluate_patterns(&opp_patterns);
    
    // Add positional bonuses
    score += evaluate_center_control(board);
    score += evaluate_connectivity(board) / 10; // Scale down connectivity bonus
    
    // Prioritize blocking opponent threats
    if (opp_patterns.threat_level > ai_patterns.threat_level) {
        score -= opp_patterns.threat_level * 2;
    }
    
    return score;
}

int evaluate_position(const game_board_t *board, int x, int y, player_t player)
{
    game_board_t temp_board;
    int score;
    
    copy_board(&temp_board, board);
    make_move(&temp_board, x, y, player);
    
    score = evaluate_board(&temp_board);
    
    // Add immediate threat detection bonus
    int threat_level = detect_threat(board, x, y, player);
    if (player == PLAYER_AI) {
        score += threat_level;
    } else {
        score -= threat_level;
    }
    
    // Bonus for blocking opponent threats
    int blocking_bonus = detect_threat(board, x, y, get_opponent(player));
    if (player == PLAYER_AI) {
        score += blocking_bonus / 2;
    }
    
    return score;
}
/*
** EPITECH PROJECT, 2024
** Gomoku AI
** File description:
** Main header file for Gomoku AI
*/

#ifndef GOMOKU_H_
#define GOMOKU_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#define BOARD_SIZE 20
#define WIN_LENGTH 5
#define MAX_MOVES (BOARD_SIZE * BOARD_SIZE)
#define MAX_DEPTH 6
#define TIME_LIMIT 5000  // 5 seconds in milliseconds
#define MEMORY_LIMIT (70 * 1024 * 1024)  // 70 MB

// Player types
typedef enum {
    EMPTY = 0,
    PLAYER_AI = 1,
    PLAYER_OPPONENT = 2
} player_t;

// Move structure
typedef struct {
    int x;
    int y;
    int score;
} move_t;

// Game board structure
typedef struct {
    int board[BOARD_SIZE][BOARD_SIZE];
    int move_count;
    move_t last_move;
    player_t current_player;
} game_board_t;

// Pattern types for evaluation
typedef enum {
    PATTERN_FIVE = 0,
    PATTERN_OPEN_FOUR,
    PATTERN_FOUR,
    PATTERN_OPEN_THREE,
    PATTERN_THREE,
    PATTERN_OPEN_TWO,
    PATTERN_TWO,
    PATTERN_ONE,
    PATTERN_COUNT
} pattern_type_t;

// Pattern structure
typedef struct {
    int count[PATTERN_COUNT];
    int threat_level;
} pattern_eval_t;

// Time management structure
typedef struct {
    struct timeval start_time;
    long time_limit_ms;
    int max_depth;
} time_manager_t;

// Protocol functions
int handle_protocol(void);
void process_command(char *command);
void send_response(const char *response);

// Board functions
void init_board(game_board_t *board);
void copy_board(game_board_t *dest, const game_board_t *src);
int is_valid_move(const game_board_t *board, int x, int y);
void make_move(game_board_t *board, int x, int y, player_t player);
void undo_move(game_board_t *board, int x, int y);
void print_board(const game_board_t *board);

// Game logic functions
int check_win(const game_board_t *board, int x, int y, player_t player);
int is_game_over(const game_board_t *board);
int count_consecutive(const game_board_t *board, int x, int y, int dx, int dy, player_t player);

// Pattern recognition functions
void analyze_patterns(const game_board_t *board, pattern_eval_t *ai_patterns, pattern_eval_t *opp_patterns);
int detect_threat(const game_board_t *board, int x, int y, player_t player);
int is_winning_move(const game_board_t *board, int x, int y, player_t player);
int is_blocking_move(const game_board_t *board, int x, int y, player_t opponent);

// Minimax algorithm functions
int minimax(game_board_t *board, int depth, int alpha, int beta, int maximizing_player, time_manager_t *time_mgr);
move_t find_best_move(game_board_t *board, time_manager_t *time_mgr);

// Evaluation functions
int evaluate_board(const game_board_t *board);
int evaluate_position(const game_board_t *board, int x, int y, player_t player);
int pattern_score(pattern_type_t type);

// Move generation functions
int generate_moves(const game_board_t *board, move_t *moves, int max_moves);
void sort_moves(move_t *moves, int count);
int is_near_stones(const game_board_t *board, int x, int y, int radius);

// Time management functions
void init_time_manager(time_manager_t *time_mgr, long time_limit_ms);
long get_elapsed_time(const time_manager_t *time_mgr);
int is_time_up(const time_manager_t *time_mgr);

// Utility functions
player_t get_opponent(player_t player);
int max(int a, int b);
int min(int a, int b);

// Global variables
extern game_board_t g_board;
extern player_t g_ai_player;

#endif /* !GOMOKU_H_ */
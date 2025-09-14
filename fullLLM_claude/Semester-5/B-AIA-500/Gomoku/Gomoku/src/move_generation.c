/*
** EPITECH PROJECT, 2024
** Gomoku AI
** File description:
** Move generation and ordering for efficient search
*/

#include "gomoku.h"

int is_near_stones(const game_board_t *board, int x, int y, int radius)
{
    int i, j;
    
    for (i = max(0, y - radius); i <= min(BOARD_SIZE - 1, y + radius); i++) {
        for (j = max(0, x - radius); j <= min(BOARD_SIZE - 1, x + radius); j++) {
            if (board->board[i][j] != (int)EMPTY) {
                return 1;
            }
        }
    }
    return 0;
}

static int compare_moves(const void *a, const void *b)
{
    const move_t *move_a = (const move_t *)a;
    const move_t *move_b = (const move_t *)b;
    
    return move_b->score - move_a->score; // Descending order
}

void sort_moves(move_t *moves, int count)
{
    qsort(moves, count, sizeof(move_t), compare_moves);
}

static int generate_threat_moves(const game_board_t *board, move_t *moves, int max_moves)
{
    int count = 0;
    int i, j;
    
    // First, check for winning moves
    for (i = 0; i < BOARD_SIZE && count < max_moves; i++) {
        for (j = 0; j < BOARD_SIZE && count < max_moves; j++) {
            if (is_valid_move(board, j, i)) {
                if (is_winning_move(board, j, i, PLAYER_AI)) {
                    moves[count].x = j;
                    moves[count].y = i;
                    moves[count].score = 1000000;
                    count++;
                    return count; // Return immediately with winning move
                }
            }
        }
    }
    
    // Then, check for blocking moves
    for (i = 0; i < BOARD_SIZE && count < max_moves; i++) {
        for (j = 0; j < BOARD_SIZE && count < max_moves; j++) {
            if (is_valid_move(board, j, i)) {
                if (is_blocking_move(board, j, i, PLAYER_OPPONENT)) {
                    moves[count].x = j;
                    moves[count].y = i;
                    moves[count].score = 500000;
                    count++;
                }
            }
        }
    }
    
    return count;
}

static int generate_tactical_moves(const game_board_t *board, move_t *moves, int max_moves, int existing_count)
{
    int count = existing_count;
    int i, j;
    
    // Generate moves that create threats or improve position
    for (i = 0; i < BOARD_SIZE && count < max_moves; i++) {
        for (j = 0; j < BOARD_SIZE && count < max_moves; j++) {
            if (is_valid_move(board, j, i) && is_near_stones(board, j, i, 2)) {
                int threat_score = detect_threat(board, j, i, PLAYER_AI);
                int block_score = detect_threat(board, j, i, PLAYER_OPPONENT);
                
                if (threat_score > 100 || block_score > 100) {
                    moves[count].x = j;
                    moves[count].y = i;
                    moves[count].score = threat_score + block_score / 2;
                    count++;
                }
            }
        }
    }
    
    return count;
}

static int generate_positional_moves(const game_board_t *board, move_t *moves, int max_moves, int existing_count)
{
    int count = existing_count;
    int center = BOARD_SIZE / 2;
    int i, j;
    
    // If board is empty, play center
    if (board->move_count == 0) {
        if (count < max_moves) {
            moves[count].x = center;
            moves[count].y = center;
            moves[count].score = 1000;
            count++;
        }
        return count;
    }
    
    // Generate moves near existing stones
    for (i = 0; i < BOARD_SIZE && count < max_moves; i++) {
        for (j = 0; j < BOARD_SIZE && count < max_moves; j++) {
            if (is_valid_move(board, j, i) && is_near_stones(board, j, i, 2)) {
                int position_score = evaluate_position(board, j, i, PLAYER_AI);
                
                // Skip if already added as tactical move
                int already_added = 0;
                int k;
                for (k = 0; k < count; k++) {
                    if (moves[k].x == j && moves[k].y == i) {
                        already_added = 1;
                        break;
                    }
                }
                
                if (!already_added) {
                    moves[count].x = j;
                    moves[count].y = i;
                    moves[count].score = position_score;
                    count++;
                }
            }
        }
    }
    
    return count;
}

int generate_moves(const game_board_t *board, move_t *moves, int max_moves)
{
    int count = 0;
    
    // Generate moves in order of priority
    count = generate_threat_moves(board, moves, max_moves);
    if (count > 0 && moves[0].score >= 1000000) {
        return count; // Return immediately if winning move found
    }
    
    count = generate_tactical_moves(board, moves, max_moves, count);
    count = generate_positional_moves(board, moves, max_moves, count);
    
    // Sort moves by score
    sort_moves(moves, count);
    
    // Limit to reasonable number for search efficiency
    if (count > 20) {
        count = 20;
    }
    
    return count;
}
/*
** EPITECH PROJECT, 2024
** Gomoku AI
** File description:
** Minimax algorithm with alpha-beta pruning
*/

#include "gomoku.h"

#define INFINITY 2000000
#define NEG_INFINITY -2000000

static int nodes_evaluated = 0;

int minimax(game_board_t *board, int depth, int alpha, int beta, int maximizing_player, time_manager_t *time_mgr)
{
    int score, best_score;
    move_t moves[50];
    int move_count, i;
    
    nodes_evaluated++;
    
    // Check time limit periodically
    if (nodes_evaluated % 1000 == 0 && is_time_up(time_mgr)) {
        return 0; // Return neutral score when time is up
    }
    
    // Base case: evaluate leaf node
    if (depth == 0 || is_game_over(board)) {
        return evaluate_board(board);
    }
    
    // Generate possible moves
    move_count = generate_moves(board, moves, 50);
    
    if (move_count == 0) {
        return evaluate_board(board);
    }
    
    if (maximizing_player) {
        best_score = NEG_INFINITY;
        
        for (i = 0; i < move_count; i++) {
            make_move(board, moves[i].x, moves[i].y, PLAYER_AI);
            
            score = minimax(board, depth - 1, alpha, beta, 0, time_mgr);
            
            undo_move(board, moves[i].x, moves[i].y);
            
            if (score > best_score) {
                best_score = score;
            }
            
            alpha = max(alpha, best_score);
            
            // Alpha-beta pruning
            if (beta <= alpha) {
                break;
            }
            
            // Early termination for winning moves
            if (best_score >= 1000000) {
                break;
            }
        }
        
        return best_score;
    } else {
        best_score = INFINITY;
        
        for (i = 0; i < move_count; i++) {
            make_move(board, moves[i].x, moves[i].y, PLAYER_OPPONENT);
            
            score = minimax(board, depth - 1, alpha, beta, 1, time_mgr);
            
            undo_move(board, moves[i].x, moves[i].y);
            
            if (score < best_score) {
                best_score = score;
            }
            
            beta = min(beta, best_score);
            
            // Alpha-beta pruning
            if (beta <= alpha) {
                break;
            }
            
            // Early termination for losing moves
            if (best_score <= -1000000) {
                break;
            }
        }
        
        return best_score;
    }
}

move_t find_best_move(game_board_t *board, time_manager_t *time_mgr)
{
    move_t best_move = {-1, -1, NEG_INFINITY};
    move_t moves[50];
    int move_count;
    int i, depth;
    
    nodes_evaluated = 0;
    
    // Generate possible moves
    move_count = generate_moves(board, moves, 50);
    
    if (move_count == 0) {
        // Fallback: play center if board is empty, otherwise find any valid move
        int center = BOARD_SIZE / 2;
        if (is_valid_move(board, center, center)) {
            best_move.x = center;
            best_move.y = center;
            best_move.score = 1000;
        } else {
            // Find any valid move
            for (i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    if (is_valid_move(board, j, i)) {
                        best_move.x = j;
                        best_move.y = i;
                        best_move.score = 0;
                        return best_move;
                    }
                }
            }
        }
        return best_move;
    }
    
    // Check for immediate winning moves
    for (i = 0; i < move_count; i++) {
        if (is_winning_move(board, moves[i].x, moves[i].y, PLAYER_AI)) {
            best_move = moves[i];
            best_move.score = 1000000;
            return best_move;
        }
    }
    
    // Check for immediate blocking moves
    for (i = 0; i < move_count; i++) {
        if (is_blocking_move(board, moves[i].x, moves[i].y, PLAYER_OPPONENT)) {
            best_move = moves[i];
            best_move.score = 500000;
            // Don't return immediately, there might be a better move
        }
    }
    
    // Iterative deepening search
    for (depth = 1; depth <= time_mgr->max_depth && !is_time_up(time_mgr); depth++) {
        int best_score = NEG_INFINITY;
        move_t current_best = {-1, -1, NEG_INFINITY};
        
        for (i = 0; i < move_count && !is_time_up(time_mgr); i++) {
            make_move(board, moves[i].x, moves[i].y, PLAYER_AI);
            
            int score = minimax(board, depth - 1, NEG_INFINITY, INFINITY, 0, time_mgr);
            
            undo_move(board, moves[i].x, moves[i].y);
            
            if (score > best_score) {
                best_score = score;
                current_best.x = moves[i].x;
                current_best.y = moves[i].y;
                current_best.score = score;
            }
            
            // Early termination for winning moves
            if (score >= 1000000) {
                best_move = current_best;
                return best_move;
            }
        }
        
        // Update best move if we completed the depth
        if (!is_time_up(time_mgr) && current_best.x != -1) {
            best_move = current_best;
        }
        
        // Debug info
        fprintf(stderr, "Depth %d completed: best move (%d,%d) with score %d, nodes: %d\n", 
                depth, best_move.x, best_move.y, best_move.score, nodes_evaluated);
    }
    
    // Final validation
    if (best_move.x == -1 || best_move.y == -1 || !is_valid_move(board, best_move.x, best_move.y)) {
        // Emergency fallback: return first valid move
        for (i = 0; i < move_count; i++) {
            if (is_valid_move(board, moves[i].x, moves[i].y)) {
                best_move = moves[i];
                break;
            }
        }
    }
    
    return best_move;
}
/*
** EPITECH PROJECT, 2024
** Gomoku AI
** File description:
** Protocol handling for game communication
*/

#include "gomoku.h"

static void handle_start(char *command)
{
    int size;
    
    if (sscanf(command, "START %d", &size) == 1) {
        if (size == BOARD_SIZE) {
            send_response("OK");
            init_board(&g_board);
        } else {
            send_response("ERROR");
        }
    } else {
        send_response("ERROR");
    }
}

static void handle_turn(char *command)
{
    int x, y;
    time_manager_t time_mgr;
    move_t best_move;
    
    if (sscanf(command, "TURN %d,%d", &x, &y) == 2) {
        if (is_valid_move(&g_board, x, y)) {
            make_move(&g_board, x, y, PLAYER_OPPONENT);
            
            init_time_manager(&time_mgr, TIME_LIMIT);
            best_move = find_best_move(&g_board, &time_mgr);
            
            if (is_valid_move(&g_board, best_move.x, best_move.y)) {
                make_move(&g_board, best_move.x, best_move.y, PLAYER_AI);
                printf("%d,%d\n", best_move.x, best_move.y);
                fflush(stdout);
            } else {
                send_response("ERROR");
            }
        } else {
            send_response("ERROR");
        }
    } else {
        send_response("ERROR");
    }
}

static void handle_begin(void)
{
    time_manager_t time_mgr;
    move_t best_move;
    
    init_time_manager(&time_mgr, TIME_LIMIT);
    best_move = find_best_move(&g_board, &time_mgr);
    
    if (is_valid_move(&g_board, best_move.x, best_move.y)) {
        make_move(&g_board, best_move.x, best_move.y, PLAYER_AI);
        printf("%d,%d\n", best_move.x, best_move.y);
        fflush(stdout);
    } else {
        // Fallback to center position
        int center = BOARD_SIZE / 2;
        make_move(&g_board, center, center, PLAYER_AI);
        printf("%d,%d\n", center, center);
        fflush(stdout);
    }
}

static void handle_board(void)
{
    char line[256];
    int x, y, player;
    
    init_board(&g_board);
    
    while (fgets(line, sizeof(line), stdin)) {
        if (strcmp(line, "DONE\n") == 0) {
            break;
        }
        
        if (sscanf(line, "%d,%d,%d", &x, &y, &player) == 3) {
            if (is_valid_move(&g_board, x, y)) {
                if (player == 1) {
                    make_move(&g_board, x, y, PLAYER_AI);
                } else if (player == 2) {
                    make_move(&g_board, x, y, PLAYER_OPPONENT);
                }
            }
        }
    }
    
    time_manager_t time_mgr;
    init_time_manager(&time_mgr, TIME_LIMIT);
    move_t best_move = find_best_move(&g_board, &time_mgr);
    
    if (is_valid_move(&g_board, best_move.x, best_move.y)) {
        make_move(&g_board, best_move.x, best_move.y, PLAYER_AI);
        printf("%d,%d\n", best_move.x, best_move.y);
        fflush(stdout);
    } else {
        send_response("ERROR");
    }
}

void process_command(char *command)
{
    // Remove newline character
    command[strcspn(command, "\n")] = 0;
    
    if (strncmp(command, "START", 5) == 0) {
        handle_start(command);
    } else if (strncmp(command, "TURN", 4) == 0) {
        handle_turn(command);
    } else if (strcmp(command, "BEGIN") == 0) {
        handle_begin();
    } else if (strcmp(command, "BOARD") == 0) {
        handle_board();
    } else if (strcmp(command, "INFO") == 0) {
        // Read and ignore INFO commands
        char info_line[256];
        while (fgets(info_line, sizeof(info_line), stdin)) {
            if (strcmp(info_line, "DONE\n") == 0) {
                break;
            }
        }
        send_response("OK");
    } else if (strcmp(command, "END") == 0) {
        exit(0);
    } else {
        send_response("UNKNOWN");
    }
}

void send_response(const char *response)
{
    printf("%s\n", response);
    fflush(stdout);
}

int handle_protocol(void)
{
    char command[256];
    
    while (fgets(command, sizeof(command), stdin)) {
        process_command(command);
    }
    
    return 0;
}
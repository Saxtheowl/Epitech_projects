/*
** EPITECH PROJECT, 2024
** Gomoku AI
** File description:
** Main entry point for Gomoku AI
*/

#include "gomoku.h"

game_board_t g_board;
player_t g_ai_player = PLAYER_AI;

int main(void)
{
    init_board(&g_board);
    return handle_protocol();
}
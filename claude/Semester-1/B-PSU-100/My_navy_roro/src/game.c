/*
** EPITECH PROJECT, 2024
** My_navy
** File description:
** Game logic for my_navy
*/

#include "../include/my_navy.h"

int check_hit(game_t *game, int x, int y)
{
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE)
        return 0;
    if (game->my_board[y][x] != '.' && game->my_board[y][x] != 'x' &&
        game->my_board[y][x] != 'o') {
        game->my_board[y][x] = 'x';
        return 1;
    }
    if (game->my_board[y][x] == '.')
        game->my_board[y][x] = 'o';
    return 0;
}

void update_enemy_board(game_t *game, int x, int y, int hit)
{
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE)
        return;
    game->enemy_board[y][x] = hit ? 'x' : 'o';
}

int check_game_over(game_t *game)
{
    int i, j;
    int my_ships_alive = 0;
    int enemy_ships_alive = 0;

    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (game->my_board[i][j] >= '2' && game->my_board[i][j] <= '5')
                my_ships_alive = 1;
            if (game->enemy_board[i][j] == '.')
                enemy_ships_alive = 1;
        }
    }
    if (!my_ships_alive) {
        game->game_over = 1;
        game->winner = 1;
        return 1;
    }
    if (!enemy_ships_alive) {
        game->game_over = 1;
        game->winner = 0;
        return 1;
    }
    return 0;
}

static int handle_enemy_turn(game_t *game)
{
    int hit;

    my_putstr("waiting for enemy's attack...\n");
    receive_position();
    hit = check_hit(game, game->attack_x, game->attack_y);
    my_putstr("result: ");
    my_putchar('A' + game->attack_x);
    my_putnbr(game->attack_y + 1);
    my_putstr(hit ? ":hit\n" : ":missed\n");
    send_position(game->enemy_pid, game->attack_x, game->attack_y);
    send_position(game->enemy_pid, hit, 0);
    return 0;
}

static int handle_my_turn(game_t *game)
{
    char input[10];
    int x, y, hit;

    display_boards(game);
    while (1) {
        my_putstr("attack: ");
        if (fgets(input, sizeof(input), stdin) == NULL)
            return -1;
        if (input[my_strlen(input) - 1] == '\n')
            input[my_strlen(input) - 1] = '\0';
        if (is_valid_position(input))
            break;
        my_putstr("wrong position\n");
    }
    parse_position(input, &x, &y);
    send_position(game->enemy_pid, x, y);
    my_putstr("waiting for enemy's attack...\n");
    receive_position();
    hit = game->attack_x;
    update_enemy_board(game, x, y, hit);
    my_putstr("result: ");
    my_putchar('A' + x);
    my_putnbr(y + 1);
    my_putstr(hit ? ":hit\n" : ":missed\n");
    return 0;
}

int play_turn(game_t *game)
{
    if (game->turn)
        return handle_my_turn(game);
    else
        return handle_enemy_turn(game);
}
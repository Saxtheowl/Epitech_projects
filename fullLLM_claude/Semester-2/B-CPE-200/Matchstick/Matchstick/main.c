/*
** EPITECH PROJECT, 2024
** Matchstick
** File description:
** Matchstick game implementation - Nim game
*/

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define MAX_LINES 100

typedef struct {
    int lines;
    int max_matches;
    int *matchsticks;
    int total_matches;
} game_t;

int my_strlen(char *str)
{
    int len = 0;
    
    if (!str)
        return 0;
    while (str[len])
        len++;
    return len;
}

int my_atoi(char *str)
{
    int result = 0;
    int i = 0;
    
    if (!str)
        return -1;
    if (str[0] == '-')
        return -1;
    while (str[i]) {
        if (str[i] < '0' || str[i] > '9')
            return -1;
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result;
}

void my_putstr(char *str)
{
    if (str)
        write(1, str, my_strlen(str));
}

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putnbr(int nb)
{
    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    if (nb >= 10) {
        my_putnbr(nb / 10);
    }
    my_putchar(nb % 10 + '0');
}

void display_board(game_t *game)
{
    int i, j;
    
    my_putstr("\n");
    for (i = 0; i < game->lines; i++) {
        my_putnbr(i + 1);
        my_putstr(": ");
        for (j = 0; j < game->matchsticks[i]; j++) {
            my_putstr("| ");
        }
        my_putstr("\n");
    }
    my_putstr("\n");
}

int init_game(game_t *game, int lines, int max_matches)
{
    int i;
    
    if (lines <= 1 || lines >= MAX_LINES || max_matches <= 0)
        return -1;
    
    game->lines = lines;
    game->max_matches = max_matches;
    game->matchsticks = malloc(sizeof(int) * lines);
    if (!game->matchsticks)
        return -1;
    
    game->total_matches = 0;
    for (i = 0; i < lines; i++) {
        game->matchsticks[i] = 2 * i + 1;
        game->total_matches += game->matchsticks[i];
    }
    
    return 0;
}

char *get_input(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read_len;
    
    read_len = getline(&line, &len, stdin);
    if (read_len == -1) {
        if (line)
            free(line);
        return NULL;
    }
    
    if (read_len > 0 && line[read_len - 1] == '\n')
        line[read_len - 1] = '\0';
    
    return line;
}

int get_player_move(game_t *game, int *line, int *matches)
{
    char *input;
    
    while (1) {
        my_putstr("Line: ");
        input = get_input();
        if (!input)
            return -1;
        
        *line = my_atoi(input);
        free(input);
        
        if (*line < 1 || *line > game->lines) {
            my_putstr("Error: this line is out of range\n");
            continue;
        }
        
        if (game->matchsticks[*line - 1] == 0) {
            my_putstr("Error: this line is empty\n");
            continue;
        }
        
        break;
    }
    
    while (1) {
        my_putstr("Matches: ");
        input = get_input();
        if (!input)
            return -1;
        
        *matches = my_atoi(input);
        free(input);
        
        if (*matches <= 0) {
            my_putstr("Error: you have to remove at least one match\n");
            continue;
        }
        
        if (*matches > game->max_matches) {
            my_putstr("Error: you cannot remove more than ");
            my_putnbr(game->max_matches);
            my_putstr(" matches per turn\n");
            continue;
        }
        
        if (*matches > game->matchsticks[*line - 1]) {
            my_putstr("Error: not enough matches on this line\n");
            continue;
        }
        
        break;
    }
    
    return 0;
}

int calculate_nim_sum(game_t *game)
{
    int nim_sum = 0;
    int i;
    
    for (i = 0; i < game->lines; i++) {
        nim_sum ^= game->matchsticks[i];
    }
    return nim_sum;
}

void make_ai_move(game_t *game)
{
    int nim_sum = calculate_nim_sum(game);
    int i, target;
    
    my_putstr("AI's turn...\n");
    
    if (nim_sum == 0) {
        // Losing position, make a random move
        do {
            i = random() % game->lines;
        } while (game->matchsticks[i] == 0);
        
        target = (random() % game->matchsticks[i]) + 1;
        if (target > game->max_matches)
            target = game->max_matches;
    } else {
        // Winning position, find the optimal move
        for (i = 0; i < game->lines; i++) {
            target = game->matchsticks[i] ^ nim_sum;
            if (target < game->matchsticks[i]) {
                int remove = game->matchsticks[i] - target;
                if (remove <= game->max_matches) {
                    target = remove;
                    break;
                }
            }
        }
        
        // If no optimal move found within max_matches limit, make random move
        if (i == game->lines) {
            do {
                i = random() % game->lines;
            } while (game->matchsticks[i] == 0);
            
            target = (random() % game->matchsticks[i]) + 1;
            if (target > game->max_matches)
                target = game->max_matches;
        }
    }
    
    my_putstr("AI removed ");
    my_putnbr(target);
    my_putstr(" match(es) from line ");
    my_putnbr(i + 1);
    my_putstr("\n");
    
    game->matchsticks[i] -= target;
    game->total_matches -= target;
}

int is_game_over(game_t *game)
{
    return game->total_matches == 0;
}

int play_game(game_t *game)
{
    int player_turn = 1;
    int line, matches;
    
    srandom(time(NULL) ^ getpid());
    
    display_board(game);
    
    while (!is_game_over(game)) {
        if (player_turn) {
            my_putstr("Your turn:\n");
            if (get_player_move(game, &line, &matches) == -1)
                return -1;
            
            my_putstr("Player removed ");
            my_putnbr(matches);
            my_putstr(" match(es) from line ");
            my_putnbr(line);
            my_putstr("\n");
            
            game->matchsticks[line - 1] -= matches;
            game->total_matches -= matches;
        } else {
            make_ai_move(game);
        }
        
        display_board(game);
        
        if (is_game_over(game)) {
            if (player_turn) {
                my_putstr("You lost, too bad...\n");
                return 2;
            } else {
                my_putstr("I lost... snif... but I'll get you next time!!\n");
                return 1;
            }
        }
        
        player_turn = !player_turn;
    }
    
    return 0;
}

int main(int argc, char **argv)
{
    game_t game;
    int lines, max_matches;
    int result;
    
    if (argc != 3) {
        write(2, "Usage: ./matchstick <lines> <max_matches>\n", 42);
        return 84;
    }
    
    lines = my_atoi(argv[1]);
    max_matches = my_atoi(argv[2]);
    
    if (init_game(&game, lines, max_matches) == -1) {
        write(2, "Error: invalid parameters\n", 26);
        return 84;
    }
    
    result = play_game(&game);
    
    free(game.matchsticks);
    
    if (result == -1)
        return 84;
    
    return result;
}
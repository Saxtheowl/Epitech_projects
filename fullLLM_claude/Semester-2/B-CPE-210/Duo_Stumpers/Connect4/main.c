/*
** EPITECH PROJECT, 2024
** Connect4
** File description:
** Connect 4 game implementation
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    int width;
    int height;
    char p1_avatar;
    char p2_avatar;
    char referee;
    char **board;
    int current_player;
} game_t;

void print_usage(void)
{
    fprintf(stderr, "Usage: connect4 [-w WIDTH] [-h HEIGHT] [-p1 AVATAR] [-p2 AVATAR] [-a REFEREE]\n");
}

int validate_params(game_t *game)
{
    if (game->width > 80 || game->height > 16) {
        fprintf(stderr, "Grid size cannot exceed 80 columns and 16 rows\n");
        return 84;
    }
    
    if (game->width * game->height < 20) {
        fprintf(stderr, "Grid must have at least 20 slots\n");
        return 84;
    }
    
    if (game->p1_avatar == game->p2_avatar || 
        game->p1_avatar == game->referee || 
        game->p2_avatar == game->referee) {
        fprintf(stderr, "All avatars must be different\n");
        return 84;
    }
    
    return 0;
}

int init_game(game_t *game)
{
    int i, j;
    
    game->board = malloc(sizeof(char*) * game->height);
    if (!game->board)
        return 84;
    
    for (i = 0; i < game->height; i++) {
        game->board[i] = malloc(sizeof(char) * game->width);
        if (!game->board[i])
            return 84;
        for (j = 0; j < game->width; j++) {
            game->board[i][j] = '.';
        }
    }
    
    return 0;
}

void free_game(game_t *game)
{
    int i;
    
    if (game->board) {
        for (i = 0; i < game->height; i++) {
            free(game->board[i]);
        }
        free(game->board);
    }
}

void print_board(game_t *game)
{
    int i, j;
    
    for (i = 0; i < game->width + 2; i++)
        printf("+");
    printf("\n");
    
    for (i = 0; i < game->height; i++) {
        printf("|");
        for (j = 0; j < game->width; j++) {
            printf("%c", game->board[i][j]);
        }
        printf("|\n");
    }
    
    for (i = 0; i < game->width + 2; i++)
        printf("+");
    printf("\n");
}

int drop_piece(game_t *game, int col)
{
    int row;
    char avatar = (game->current_player == 1) ? game->p1_avatar : game->p2_avatar;
    
    if (col < 1 || col > game->width)
        return -1;
    
    col--; // Convert to 0-based index
    
    // Check if column is full
    if (game->board[0][col] != '.')
        return -1;
    
    // Drop piece to lowest available position
    for (row = game->height - 1; row >= 0; row--) {
        if (game->board[row][col] == '.') {
            game->board[row][col] = avatar;
            return row;
        }
    }
    
    return -1;
}

int check_win_direction(game_t *game, int row, int col, int dr, int dc, char avatar)
{
    int count = 0;
    int r = row;
    int c = col;
    
    // Count in positive direction
    while (r >= 0 && r < game->height && c >= 0 && c < game->width && 
           game->board[r][c] == avatar) {
        count++;
        r += dr;
        c += dc;
    }
    
    // Count in negative direction (excluding center piece)
    r = row - dr;
    c = col - dc;
    while (r >= 0 && r < game->height && c >= 0 && c < game->width && 
           game->board[r][c] == avatar) {
        count++;
        r -= dr;
        c -= dc;
    }
    
    return count >= 4;
}

void mark_winning_pieces(game_t *game, int row, int col, int dr, int dc, char avatar)
{
    int r = row;
    int c = col;
    
    // Mark in positive direction
    while (r >= 0 && r < game->height && c >= 0 && c < game->width && 
           game->board[r][c] == avatar) {
        game->board[r][c] = game->referee;
        r += dr;
        c += dc;
    }
    
    // Mark in negative direction (excluding center piece which is already marked)
    r = row - dr;
    c = col - dc;
    while (r >= 0 && r < game->height && c >= 0 && c < game->width && 
           game->board[r][c] == avatar) {
        game->board[r][c] = game->referee;
        r -= dr;
        c -= dc;
    }
}

int check_win(game_t *game, int last_row, int last_col)
{
    char avatar = (game->current_player == 1) ? game->p1_avatar : game->p2_avatar;
    int directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};
    int i;
    
    for (i = 0; i < 4; i++) {
        if (check_win_direction(game, last_row, last_col, 
                               directions[i][0], directions[i][1], avatar)) {
            mark_winning_pieces(game, last_row, last_col,
                               directions[i][0], directions[i][1], avatar);
            return 1;
        }
    }
    
    return 0;
}

int is_board_full(game_t *game)
{
    int j;
    
    for (j = 0; j < game->width; j++) {
        if (game->board[0][j] == '.')
            return 0;
    }
    
    return 1;
}

int parse_args(int argc, char **argv, game_t *game)
{
    int i;
    
    // Set defaults
    game->width = 7;
    game->height = 6;
    game->p1_avatar = 'X';
    game->p2_avatar = 'O';
    game->referee = '#';
    game->current_player = 1;
    
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-w") == 0 && i + 1 < argc) {
            game->width = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-h") == 0 && i + 1 < argc) {
            game->height = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-p1") == 0 && i + 1 < argc) {
            game->p1_avatar = argv[++i][0];
        } else if (strcmp(argv[i], "-p2") == 0 && i + 1 < argc) {
            game->p2_avatar = argv[++i][0];
        } else if (strcmp(argv[i], "-a") == 0 && i + 1 < argc) {
            game->referee = argv[++i][0];
        } else {
            print_usage();
            return 84;
        }
    }
    
    return validate_params(game);
}

int main(int argc, char **argv)
{
    game_t game;
    int col, last_row;
    char input[256];
    
    if (parse_args(argc, argv, &game) != 0)
        return 84;
    
    if (init_game(&game) != 0) {
        free_game(&game);
        return 84;
    }
    
    while (1) {
        char current_avatar = (game.current_player == 1) ? game.p1_avatar : game.p2_avatar;
        
        printf("Player %c, where do you want to play: ", current_avatar);
        
        if (!fgets(input, sizeof(input), stdin)) {
            free_game(&game);
            return 0;
        }
        
        col = atoi(input);
        
        last_row = drop_piece(&game, col);
        if (last_row == -1) {
            continue; // Invalid move, ask again
        }
        
        print_board(&game);
        
        if (check_win(&game, last_row, col - 1)) {
            printf("Congrats, player %c won!\n", current_avatar);
            break;
        }
        
        if (is_board_full(&game)) {
            printf("It's a tie, nobody wins.\n");
            break;
        }
        
        game.current_player = (game.current_player == 1) ? 2 : 1;
    }
    
    free_game(&game);
    return 0;
}
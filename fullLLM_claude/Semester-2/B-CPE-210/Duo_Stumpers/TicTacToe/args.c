#include "tictactoe.h"

int parse_args(int ac, char **av, game_t *game)
{
    int i = 1;
    
    while (i < ac) {
        if (strcmp(av[i], "-p1") == 0) {
            if (i + 1 >= ac) {
                return 1;
            }
            game->player1_char = av[i + 1][0];
            i += 2;
        } else if (strcmp(av[i], "-p2") == 0) {
            if (i + 1 >= ac) {
                return 1;
            }
            game->player2_char = av[i + 1][0];
            i += 2;
        } else if (strcmp(av[i], "-s") == 0) {
            if (i + 1 >= ac) {
                return 1;
            }
            game->size = atoi(av[i + 1]);
            if (game->size <= 0) {
                return 1;
            }
            i += 2;
        } else {
            return 1;
        }
    }
    
    return 0;
}
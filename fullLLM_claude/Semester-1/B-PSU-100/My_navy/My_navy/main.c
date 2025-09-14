#include "my_navy.h"

game_state_t g_game;

int main(int argc, char **argv)
{
    if (argc == 2 && my_strcmp(argv[1], "-h") == 0) {
        display_help();
        return 0;
    }
    
    if (argc == 2) {
        g_game.my_pid = getpid();
        g_game.enemy_pid = 0;
        g_game.is_my_turn = 1;
        
        if (parse_positions_file(argv[1]) == 84)
            return 84;
            
        init_game_state();
        setup_signal_handlers();
        
        my_putstr("my_pid: ");
        my_put_nbr(g_game.my_pid);
        my_putstr("\nwaiting for enemy...\n");
        
        while (g_game.enemy_pid == 0)
            pause();
            
        my_putstr("enemy connected\n");
        game_loop();
        
    } else if (argc == 3) {
        g_game.my_pid = getpid();
        g_game.enemy_pid = 0;
        g_game.is_my_turn = 0;
        
        int i = 0;
        while (argv[1][i]) {
            if (argv[1][i] < '0' || argv[1][i] > '9')
                return 84;
            g_game.enemy_pid = g_game.enemy_pid * 10 + (argv[1][i] - '0');
            i++;
        }
        
        if (parse_positions_file(argv[2]) == 84)
            return 84;
            
        init_game_state();
        setup_signal_handlers();
        
        my_putstr("my_pid: ");
        my_put_nbr(g_game.my_pid);
        my_putstr("\n");
        
        if (kill(g_game.enemy_pid, SIGUSR1) == 0) {
            my_putstr("successfully connected\n");
            game_loop();
        } else {
            return 84;
        }
        
    } else {
        return 84;
    }
    
    return g_game.i_won ? 0 : 1;
}
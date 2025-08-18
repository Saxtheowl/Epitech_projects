#include "my_navy.h"

game_t g_game;

void signal_handler(int sig)
{
    if (sig == SIGUSR1) {
        if (g_game.enemy_pid == 0) {
            g_game.enemy_pid = 1;
        } else {
            g_game.signal_received = 1;
        }
    } else if (sig == SIGUSR2) {
        g_game.signal_received = 2;
    }
}

void setup_signals(void)
{
    struct sigaction sa;
    
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
}

void send_attack(int x, int y)
{
    int data = (x << 4) | y;
    g_game.signal_received = data;
    kill(g_game.enemy_pid, SIGUSR1);
}

void send_attack_result(int result)
{
    g_game.signal_received = result;
    kill(g_game.enemy_pid, SIGUSR2);
}

int parse_attack_input(char *input, int *x, int *y)
{
    if (!input || my_strlen(input) != 2)
        return -1;
    
    *x = char_to_x(input[0]);
    *y = char_to_y(input[1]);
    
    if (*x == -1 || *y == -1)
        return -1;
    
    return 0;
}

int is_valid_position(int x, int y)
{
    return (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE);
}

int check_win_condition(void)
{
    if (g_game.ships_remaining == 0) {
        my_putstr("Enemy won\n");
        return 1;
    }
    if (g_game.enemy_ships_remaining == 0) {
        my_putstr("I won\n");
        return 0;
    }
    return -1;
}

int process_attack(int x, int y)
{
    if (g_game.my_grid[y][x] >= '2' && g_game.my_grid[y][x] <= '5') {
        g_game.my_grid[y][x] = 'x';
        return 1;
    }
    g_game.my_grid[y][x] = 'o';
    return 0;
}

void game_loop(void)
{
    char input[10];
    int x, y, result;
    
    while (!g_game.game_over) {
        print_game_state();
        
        if (g_game.my_turn) {
            my_putstr("attack: ");
            if (!fgets(input, sizeof(input), stdin)) {
                g_game.game_over = 1;
                break;
            }
            
            input[my_strlen(input) - 1] = '\0';
            
            if (parse_attack_input(input, &x, &y) != 0 || !is_valid_position(x, y)) {
                my_putstr("wrong position\n");
                continue;
            }
            
            send_attack(x, y);
            g_game.signal_received = 0;
            
            while (!g_game.signal_received)
                usleep(1000);
            
            if (g_game.attack_result) {
                g_game.enemy_grid[y][x] = 'x';
                g_game.enemy_ships_remaining--;
                my_putstr("result: ");
                my_putchar(x_to_char(x));
                my_putchar(y_to_char(y));
                my_putstr(":hit\n");
            } else {
                g_game.enemy_grid[y][x] = 'o';
                my_putstr("result: ");
                my_putchar(x_to_char(x));
                my_putchar(y_to_char(y));
                my_putstr(":missed\n");
            }
            
            g_game.my_turn = 0;
            
            if (check_win_condition() != -1) {
                g_game.game_over = 1;
                break;
            }
            
            my_putstr("waiting for enemy's attack...\n");
        } else {
            g_game.signal_received = 0;
            
            while (!g_game.signal_received)
                usleep(1000);
            
            result = process_attack(g_game.attack_x, g_game.attack_y);
            send_attack_result(result);
            
            if (result) {
                g_game.ships_remaining--;
                my_putstr("result: ");
                my_putchar(x_to_char(g_game.attack_x));
                my_putchar(y_to_char(g_game.attack_y));
                my_putstr(":hit\n");
            } else {
                my_putstr("result: ");
                my_putchar(x_to_char(g_game.attack_x));
                my_putchar(y_to_char(g_game.attack_y));
                my_putstr(":missed\n");
            }
            
            g_game.my_turn = 1;
            
            if (check_win_condition() != -1) {
                g_game.game_over = 1;
                break;
            }
        }
    }
}

void print_usage(void)
{
    my_putstr("USAGE\n");
    my_putstr("    ./my_navy [first_player_pid] navy_positions\n");
    my_putstr("DESCRIPTION\n");
    my_putstr("    first_player_pid: only for the 2nd player. pid of the first player.\n");
    my_putstr("    navy_positions: file representing the positions of the ships.\n");
}

int main(int ac, char **av)
{
    pid_t my_pid;
    
    if (ac == 2 && my_strcmp(av[1], "-h") == 0) {
        print_usage();
        return 0;
    }
    
    if (ac < 2 || ac > 3) {
        print_usage();
        return 84;
    }
    
    memset(&g_game, 0, sizeof(game_t));
    
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            g_game.my_grid[i][j] = '.';
            g_game.enemy_grid[i][j] = '.';
        }
    }
    
    g_game.ships_remaining = SHIP_COUNT;
    g_game.enemy_ships_remaining = SHIP_COUNT;
    
    if (parse_positions_file(av[ac - 1]) != 0) {
        my_putstr("Error: Invalid positions file\n");
        return 84;
    }
    
    my_pid = getpid();
    my_putstr("my_pid: ");
    printf("%d\n", my_pid);
    
    setup_signals();
    
    if (ac == 2) {
        g_game.my_turn = 1;
        my_putstr("waiting for enemy...\n");
        while (g_game.enemy_pid == 0)
            pause();
        my_putstr("enemy connected\n");
    } else {
        g_game.enemy_pid = my_atoi(av[1]);
        g_game.my_turn = 0;
        kill(g_game.enemy_pid, SIGUSR1);
        my_putstr("successfully connected\n");
    }
    
    game_loop();
    
    return 0;
}
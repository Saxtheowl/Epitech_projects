/*
** EPITECH PROJECT, 2024
** Tetris
** File description:
** Configuration and argument parsing
*/

#include "../include/tetris.h"

void init_default_config(game_config_t *config)
{
    config->level = DEFAULT_LEVEL;
    config->key_left = KEY_LEFT_ARROW;
    config->key_right = KEY_RIGHT_ARROW;
    config->key_turn = KEY_UP_ARROW;
    config->key_drop = KEY_DOWN_ARROW;
    config->key_quit = 'q';
    config->key_pause = ' ';
    config->map_rows = DEFAULT_ROWS;
    config->map_cols = DEFAULT_COLS;
    config->show_next = 1;
    config->debug_mode = 0;
}

int parse_key_string(const char *str)
{
    if (!str)
        return -1;
    
    if (my_strcmp(str, "^EOD") == 0)
        return KEY_LEFT_ARROW;
    if (my_strcmp(str, "^EOC") == 0)
        return KEY_RIGHT_ARROW;
    if (my_strcmp(str, "^EOA") == 0)
        return KEY_UP_ARROW;
    if (my_strcmp(str, "^EOB") == 0)
        return KEY_DOWN_ARROW;
    if (my_strcmp(str, " ") == 0 || my_strcmp(str, "(space)") == 0)
        return ' ';
    
    return str[0];
}

int parse_map_size(const char *str, int *rows, int *cols)
{
    char *comma;
    
    if (!str)
        return -1;
    
    *rows = atoi(str);
    comma = strchr(str, ',');
    if (!comma)
        return -1;
    
    *cols = atoi(comma + 1);
    
    if (*rows <= 0 || *cols <= 0)
        return -1;
    
    return 0;
}

int parse_arguments(int argc, char **argv, game_config_t *config)
{
    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"level", required_argument, 0, 'l'},
        {"key-left", required_argument, 0, 1},
        {"key-right", required_argument, 0, 2},
        {"key-turn", required_argument, 0, 3},
        {"key-drop", required_argument, 0, 4},
        {"key-quit", required_argument, 0, 5},
        {"key-pause", required_argument, 0, 6},
        {"map-size", required_argument, 0, 7},
        {"without-next", no_argument, 0, 'w'},
        {"debug", no_argument, 0, 'd'},
        {0, 0, 0, 0}
    };

    int c;
    int option_index = 0;

    while ((c = getopt_long(argc, argv, "hl:wdkl:kr:kt:kd:kq:kp:", 
                           long_options, &option_index)) != -1) {
        switch (c) {
        case 'h':
            print_help();
            exit(0);
        case 'l':
            config->level = atoi(optarg);
            if (config->level < 1)
                config->level = 1;
            break;
        case 1:
            config->key_left = parse_key_string(optarg);
            break;
        case 2:
            config->key_right = parse_key_string(optarg);
            break;
        case 3:
            config->key_turn = parse_key_string(optarg);
            break;
        case 4:
            config->key_drop = parse_key_string(optarg);
            break;
        case 5:
            config->key_quit = parse_key_string(optarg);
            break;
        case 6:
            config->key_pause = parse_key_string(optarg);
            break;
        case 7:
            if (parse_map_size(optarg, &config->map_rows, &config->map_cols) != 0) {
                print_error("Invalid map size format");
                return -1;
            }
            break;
        case 'w':
            config->show_next = 0;
            break;
        case 'd':
            config->debug_mode = 1;
            break;
        default:
            return -1;
        }
    }
    
    return 0;
}

void print_help(void)
{
    printf("Usage: ./tetris [options]\n");
    printf("Options:\n");
    printf("  --help                    Display this help\n");
    printf("  -l --level={num}          Start Tetris at level num (def: 1)\n");
    printf("  -kl --key-left={K}        Move the tetrimino LEFT using the K key (def: left arrow)\n");
    printf("  -kr --key-right={K}       Move the tetrimino RIGHT using the K key (def: right arrow)\n");
    printf("  -kt --key-turn={K}        TURN the tetrimino clockwise 90d using the K key (def: top arrow)\n");
    printf("  -kd --key-drop={K}        DROP the tetrimino using the K key (def: down arrow)\n");
    printf("  -kq --key-quit={K}        QUIT the game using the K key (def: 'q' key)\n");
    printf("  -kp --key-pause={K}       PAUSE/RESTART the game using the K key (def: space bar)\n");
    printf("  --map-size={row,col}      Set the numbers of rows and columns of the map (def: 20,10)\n");
    printf("  -w --without-next         Hide next tetrimino (def: false)\n");
    printf("  -d --debug                Debug mode (def: false)\n");
}

void debug_mode(game_t *game)
{
    int i;
    char key_str[32];

    printf("*** DEBUG MODE ***\n");
    
    if (game->config.key_left == KEY_LEFT_ARROW)
        strcpy(key_str, "^EOD");
    else if (game->config.key_left == ' ')
        strcpy(key_str, "(space)");
    else
        sprintf(key_str, "%c", game->config.key_left);
    printf("Key Left : %s\n", key_str);

    if (game->config.key_right == KEY_RIGHT_ARROW)
        strcpy(key_str, "^EOC");
    else if (game->config.key_right == ' ')
        strcpy(key_str, "(space)");
    else
        sprintf(key_str, "%c", game->config.key_right);
    printf("Key Right : %s\n", key_str);

    if (game->config.key_turn == KEY_UP_ARROW)
        strcpy(key_str, "^EOA");
    else if (game->config.key_turn == ' ')
        strcpy(key_str, "(space)");
    else
        sprintf(key_str, "%c", game->config.key_turn);
    printf("Key Turn : %s\n", key_str);

    if (game->config.key_drop == KEY_DOWN_ARROW)
        strcpy(key_str, "^EOB");
    else if (game->config.key_drop == ' ')
        strcpy(key_str, "(space)");
    else
        sprintf(key_str, "%c", game->config.key_drop);
    printf("Key Drop : %s\n", key_str);

    printf("Key Quit : %c\n", game->config.key_quit);
    
    if (game->config.key_pause == ' ')
        strcpy(key_str, "(space)");
    else
        sprintf(key_str, "%c", game->config.key_pause);
    printf("Key Pause : %s\n", key_str);

    printf("Next : %s\n", game->config.show_next ? "Yes" : "No");
    printf("Level : %d\n", game->config.level);
    printf("Size : %d*%d\n", game->config.map_rows, game->config.map_cols);
    printf("Tetriminos : %d\n", game->tetrimino_count);

    for (i = 0; i < game->tetrimino_count; i++) {
        if (!game->tetriminos[i].valid) {
            printf("Tetriminos : Name %s : Error\n", game->tetriminos[i].name);
        } else {
            printf("Tetriminos : Name %s : Size %d*%d : Color %d :\n",
                   game->tetriminos[i].name, 
                   game->tetriminos[i].width, 
                   game->tetriminos[i].height,
                   game->tetriminos[i].color);
            for (int j = 0; j < game->tetriminos[i].height; j++) {
                printf("%s\n", game->tetriminos[i].shape[j]);
            }
        }
    }
    
    printf("Press any key to start Tetris\n");
}
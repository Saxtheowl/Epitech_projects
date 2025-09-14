#include "tetris.h"

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

void print_usage(char *program_name)
{
    printf("Usage: %s [options]\n", program_name);
    printf("Options:\n");
    printf("    --help                      Display this help\n");
    printf("    -l --level={num}           Start Tetris at level num (def: 1)\n");
    printf("    -kl --key-left={K}         Move the tetrimino LEFT using the K key (def: left arrow)\n");
    printf("    -kr --key-right={K}        Move the tetrimino RIGHT using the K key (def: right arrow)\n");
    printf("    -kt --key-turn={K}         TURN the tetrimino clockwise 90d using the K key (def: top arrow)\n");
    printf("    -kd --key-drop={K}         DROP the tetrimino using the K key (def: down arrow)\n");
    printf("    -kq --key-quit={K}         QUIT the game using the K key (def: 'q' key)\n");
    printf("    -kp --key-pause={K}        PAUSE/RESTART the game using the K key (def: space bar)\n");
    printf("    --map-size={row,col}       Set the numbers of rows and columns of the map (def: 20,10)\n");
    printf("    -w --without-next          Hide next tetrimino (def: false)\n");
    printf("    -d --debug                 Debug mode (def: false)\n");
}

static int parse_key(char *str)
{
    if (strlen(str) == 1)
        return str[0];
    if (strcmp(str, "space") == 0)
        return ' ';
    return str[0];
}

static int parse_map_size(char *str, int *rows, int *cols)
{
    char *comma = strchr(str, ',');
    if (!comma)
        return -1;
    
    *comma = '\0';
    *rows = atoi(str);
    *cols = atoi(comma + 1);
    
    if (*rows <= 0 || *cols <= 0)
        return -1;
    
    return 0;
}

int parse_args(int argc, char **argv, options_t *options)
{
    int option_index = 0;
    int c;
    
    while ((c = getopt_long(argc, argv, "hl:wd", long_options, &option_index)) != -1) {
        switch (c) {
        case 'h':
            print_usage(argv[0]);
            exit(0);
        case 'l':
            options->level = atoi(optarg);
            if (options->level <= 0)
                options->level = DEFAULT_LEVEL;
            break;
        case 1: // key-left
            options->key_left = parse_key(optarg);
            break;
        case 2: // key-right
            options->key_right = parse_key(optarg);
            break;
        case 3: // key-turn
            options->key_turn = parse_key(optarg);
            break;
        case 4: // key-drop
            options->key_drop = parse_key(optarg);
            break;
        case 5: // key-quit
            options->key_quit = parse_key(optarg);
            break;
        case 6: // key-pause
            options->key_pause = parse_key(optarg);
            break;
        case 7: // map-size
            if (parse_map_size(optarg, &options->rows, &options->cols) != 0) {
                fprintf(stderr, "Invalid map size format\n");
                return -1;
            }
            break;
        case 'w':
            options->without_next = 1;
            break;
        case 'd':
            options->debug = 1;
            break;
        default:
            return -1;
        }
    }
    
    return 0;
}
#include "my_top.h"

void print_usage(void)
{
    printf("usage: ./my_top -h\n");
    printf("usage: ./my_top [-ugEs] [command [args ...]]\n");
}

static int parse_delay(const char *arg, double *delay)
{
    char *endptr;
    
    *delay = strtod(arg, &endptr);
    
    if (*endptr != '\0' || *delay <= 0.0) {
        return -1;
    }
    
    return 0;
}

static int parse_frames(const char *arg, int *frames)
{
    char *endptr;
    long val;
    
    val = strtol(arg, &endptr, 10);
    
    if (*endptr != '\0' || val <= 0) {
        return -1;
    }
    
    *frames = (int)val;
    return 0;
}

int parse_args(int argc, char **argv, top_state_t *state)
{
    int i;
    
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            print_usage();
            exit(0);
        } else if (strcmp(argv[i], "-U") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Option -U requires a username argument\n");
                return -1;
            }
            strncpy(state->filter_user, argv[i + 1], sizeof(state->filter_user) - 1);
            state->filter_user[sizeof(state->filter_user) - 1] = '\0';
            i++;
        } else if (strcmp(argv[i], "-d") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Option -d requires a delay argument\n");
                return -1;
            }
            if (parse_delay(argv[i + 1], &state->refresh_delay) != 0) {
                fprintf(stderr, "Invalid delay value: %s\n", argv[i + 1]);
                return -1;
            }
            i++;
        } else if (strcmp(argv[i], "-n") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Option -n requires a frame count argument\n");
                return -1;
            }
            if (parse_frames(argv[i + 1], &state->max_frames) != 0) {
                fprintf(stderr, "Invalid frame count: %s\n", argv[i + 1]);
                return -1;
            }
            i++;
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            print_usage();
            return -1;
        }
    }
    
    return 0;
}
#include "palindrome.h"

int main(int argc, char **argv)
{
    config_t config = {-1, -1, 10, 0, 100, -1};
    
    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        print_usage();
        return 0;
    }
    
    if (parse_args(argc, argv, &config) != 0) {
        print_error("invalid argument");
        return 84;
    }
    
    if (config.mode_n == -1) {
        print_error("invalid argument");
        return 84;
    }
    
    if (config.mode_n == 1) {
        process_n_mode(&config);
    } else {
        process_p_mode(&config);
    }
    
    return 0;
}

void print_usage(void)
{
    printf("USAGE\n");
    printf("\t./palindrome -n number -p palindrome [-b base] [-imin i] [-imax i]\n");
    printf("DESCRIPTION\n");
    printf("\t-n n\t\tinteger to be transformed (>=0)\n");
    printf("\t-p pal\t\tpalindromic number to be obtained (incompatible with the -n\n");
    printf("\t\t\toption) (>=0)\n");
    printf("\t\t\tif defined, all fitting values of n will be output\n");
    printf("\t-b base\t\tbase in which the procedure will be executed (1<b<=10) [def: 10]\n");
    printf("\t-imin i\t\tminimum number of iterations, included (>=0) [def: 0]\n");
    printf("\t-imax i\t\tmaximum number of iterations, included (>=0) [def: 100]\n");
}

void print_error(char *message)
{
    fprintf(stderr, "%s\n", message);
}
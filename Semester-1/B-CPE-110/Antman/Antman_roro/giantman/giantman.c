/*
** EPITECH PROJECT, 2024
** Antman
** File description:
** Main function for giantman (decompression) program
*/

#include "../shared/compression.h"

static void print_error(char *msg)
{
    my_putstr("Error: ");
    my_putstr(msg);
    my_putstr("\n");
}

static int my_atoi(char *str)
{
    int result = 0;
    int i = 0;
    
    if (!str)
        return -1;
    
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    
    return (str[i] == '\0') ? result : -1;
}

int main(int ac, char **av)
{
    buffer_t *input;
    buffer_t *output;
    int file_type;
    
    if (ac != 3) {
        print_error("Usage: ./giantman <file> <type>");
        return 84;
    }
    
    file_type = my_atoi(av[2]);
    if (file_type < 1 || file_type > 3) {
        print_error("File type must be 1, 2, or 3");
        return 84;
    }
    
    input = read_file(av[1]);
    if (!input) {
        print_error("Cannot read input file");
        return 84;
    }
    
    switch (file_type) {
        case 1:
            output = decompress_text(input);
            break;
        case 2:
            output = decompress_html(input);
            break;
        case 3:
            output = decompress_ppm(input);
            break;
        default:
            output = NULL;
    }
    
    if (!output) {
        print_error("Decompression failed");
        free_buffer(input);
        return 84;
    }
    
    write_buffer(output);
    
    free_buffer(input);
    free_buffer(output);
    
    return 0;
}
#include "setting_up.h"

static int my_atoi(char const *str)
{
    int result = 0;
    int i = 0;
    
    if (!str)
        return 0;
    
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    
    return result;
}

static int handle_file_mode(char const *filename)
{
    board_t *board = read_board_from_file(filename);
    square_t square;
    
    if (!board) {
        write(2, "Error\n", 6);
        return 84;
    }
    
    square = find_largest_square(board);
    place_square_on_board(board, square);
    print_board(board);
    free_board(board);
    
    return 0;
}

static int handle_generation_mode(int size, char const *pattern)
{
    board_t *board = generate_board(size, pattern);
    square_t square;
    
    if (!board) {
        write(2, "Error\n", 6);
        return 84;
    }
    
    square = find_largest_square(board);
    place_square_on_board(board, square);
    print_board(board);
    free_board(board);
    
    return 0;
}

int main(int argc, char **argv)
{
    if (argc == 2) {
        return handle_file_mode(argv[1]);
    } else if (argc == 3) {
        int size = my_atoi(argv[1]);
        if (size <= 0) {
            write(2, "Error\n", 6);
            return 84;
        }
        return handle_generation_mode(size, argv[2]);
    } else {
        write(2, "Usage: ./setting_up file OR ./setting_up size pattern\n", 54);
        return 84;
    }
}
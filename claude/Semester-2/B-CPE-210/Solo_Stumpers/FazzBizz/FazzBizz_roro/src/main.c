/*
** EPITECH PROJECT, 2025
** FazzBizz
** File description:
** Main function for fazzbizz
*/

#include "fazzbizz.h"

int main(int argc, char **argv)
{
    int start, end;

    if (argc != 3)
        return 84;
    start = atoi(argv[1]);
    end = atoi(argv[2]);
    if (end < start) {
        print_error();
        return 84;
    }
    return fazzbizz(start, end);
}
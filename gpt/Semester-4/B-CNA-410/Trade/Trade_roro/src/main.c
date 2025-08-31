/*
** EPITECH PROJECT, 2025
** Trade
** File description:
**   Entry point
*/

#include <stdio.h>
#include "trade.h"

static void print_usage(void)
{
    printf("Trade bot listening on stdin. No CLI args.\n");
}

int main(int ac, char **av)
{
    (void)av;
    if (ac != 1) {
        print_usage();
        return 84;
    }
    bot_loop();
    return 0;
}


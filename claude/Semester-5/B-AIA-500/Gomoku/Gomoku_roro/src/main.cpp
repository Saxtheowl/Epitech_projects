/*
** EPITECH PROJECT, 2025
** Gomoku
** File description:
** Main entry point for Gomoku AI
*/

#include "protocol.h"

int main(void)
{
    Protocol protocol;
    
    try {
        protocol.run();
    } catch (const std::exception &e) {
        return 84;
    }
    
    return 0;
}
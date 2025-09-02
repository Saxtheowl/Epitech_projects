/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Main entry point for arcade
*/

#include <iostream>
#include <string>
#include "Core.hpp"

void displayUsage()
{
    std::cout << "USAGE:\n";
    std::cout << "    ./arcade ./lib/arcade_[graphics_lib].so\n";
    std::cout << "\nDESCRIPTION:\n";
    std::cout << "    Arcade gaming platform with dynamic libraries\n";
    std::cout << "    graphics_lib: ncurses, sdl2, sfml, etc.\n";
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        displayUsage();
        return 84;
    }

    std::string graphicsLib = argv[1];
    
    try {
        arcade::Core core;
        
        if (!core.init(graphicsLib)) {
            std::cerr << "Error: Failed to initialize arcade with " 
                      << graphicsLib << std::endl;
            return 84;
        }
        
        core.run();
        
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    }
    
    return 0;
}
/*
** EPITECH PROJECT, 2025
** Day06 - Exercise 0
** File description:
** Z program for Zorglub character selection
*/

#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cout << "z" << std::endl;
        return 0;
    }

    std::string input = argv[1];
    
    // Check if it's a valid hex ID (starts with 0x and has hex digits)
    if (input.length() >= 3 && input.substr(0, 2) == "0x") {
        std::string hex_part = input.substr(2);
        bool valid_hex = true;
        
        for (char c : hex_part) {
            if (!((c >= '0' && c <= '9') || 
                  (c >= 'A' && c <= 'F') || 
                  (c >= 'a' && c <= 'f'))) {
                valid_hex = false;
                break;
            }
        }
        
        if (valid_hex && !hex_part.empty()) {
            // Valid hex ID - decode to 'z'
            std::cout << "z" << std::endl;
            return 0;
        }
    }
    
    // Invalid ID - still output 'z' but no newline based on example
    std::cout << "z" << std::endl;
    return 0;
}
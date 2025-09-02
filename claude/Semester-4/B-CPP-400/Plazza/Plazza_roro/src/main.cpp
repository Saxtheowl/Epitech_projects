/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Main entry point
*/

#include "Reception.hpp"
#include <iostream>
#include <stdexcept>

void printUsage(const char* programName) {
    std::cerr << "Usage: " << programName << " <multiplier> <cooks_per_kitchen> <refill_time_ms>" << std::endl;
    std::cerr << "  multiplier: Cooking time multiplier (e.g., 2.0 or 0.5)" << std::endl;
    std::cerr << "  cooks_per_kitchen: Number of cooks per kitchen" << std::endl;
    std::cerr << "  refill_time_ms: Time in milliseconds to refill ingredients" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printUsage(argv[0]);
        return 84;
    }
    
    try {
        double multiplier = std::stod(argv[1]);
        int numCooks = std::stoi(argv[2]);
        int refillTime = std::stoi(argv[3]);
        
        if (multiplier <= 0 || numCooks <= 0 || refillTime <= 0) {
            std::cerr << "Error: All parameters must be positive" << std::endl;
            return 84;
        }
        
        Reception reception(multiplier, numCooks, refillTime);
        reception.run();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: Invalid parameters - " << e.what() << std::endl;
        return 84;
    }
    
    return 0;
}
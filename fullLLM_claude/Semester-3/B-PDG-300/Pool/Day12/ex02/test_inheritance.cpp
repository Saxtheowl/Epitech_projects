/*
** EPITECH PROJECT, 2024
** Day12 PDG - Test Exercise 2
** File description:
** Test for inheritance
*/

#include "Buzz.hpp"
#include "Woody.hpp"
#include <iostream>

int main()
{
    std::cout << "=== Testing inheritance ===\n";
    
    // Test Buzz construction with name only
    Buzz buzz1("Buzz Lightyear");
    std::cout << "Buzz name: " << buzz1.getName() << std::endl;
    std::cout << "Buzz type: " << buzz1.getType() << std::endl;
    
    // Test Buzz construction with custom filename
    Buzz buzz2("Custom Buzz", "alien.txt");
    std::cout << "Custom Buzz name: " << buzz2.getName() << std::endl;
    
    // Test Woody construction with name only
    Woody woody1("Woody Pride");
    std::cout << "Woody name: " << woody1.getName() << std::endl;
    std::cout << "Woody type: " << woody1.getType() << std::endl;
    
    // Test Woody construction with custom filename
    Woody woody2("Custom Woody", "alien.txt");
    std::cout << "Custom Woody name: " << woody2.getName() << std::endl;
    
    std::cout << "\nInheritance test completed!" << std::endl;
    return 0;
}
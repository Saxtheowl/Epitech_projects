/*
** EPITECH PROJECT, 2024
** Day12 PDG - Test Exercise 4
** File description:
** Test for operator overloads
*/

#include "Toy.hpp"
#include <iostream>

int main()
{
    std::cout << "=== Testing operators ===\n";
    
    Toy a(Toy::BASIC_TOY, "REX", "example.txt");
    std::cout << a;
    a << "rawr xD";
    std::cout << a;
    
    std::cout << "\nOperators test completed!" << std::endl;
    return 0;
}
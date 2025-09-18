/*
** EPITECH PROJECT, 2024
** Day08 PDG - Chain Test
** File description:
** Test chaining for Droid class
*/

#include "Droid.hpp"
#include <iostream>

int main()
{
    // Test chaining capability
    std::cout << "=== Chain Call Test ===" << std::endl;
    
    Droid source1("Source1");
    Droid source2("Source2");
    Droid target("Target");
    
    source1.setEnergy(80);
    source2.setEnergy(60);
    target.setEnergy(10);
    
    std::cout << "Before chaining:" << std::endl;
    std::cout << "Target energy: " << target.getEnergy() << std::endl;
    std::cout << "Source1 energy: " << source1.getEnergy() << std::endl;
    std::cout << "Source2 energy: " << source2.getEnergy() << std::endl;
    
    // Chain calls: target << source1 << source2
    target << source1 << source2;
    
    std::cout << "\nAfter chaining (target << source1 << source2):" << std::endl;
    std::cout << "Target energy: " << target.getEnergy() << std::endl;
    std::cout << "Source1 energy: " << source1.getEnergy() << std::endl;
    std::cout << "Source2 energy: " << source2.getEnergy() << std::endl;
    
    return 0;
}
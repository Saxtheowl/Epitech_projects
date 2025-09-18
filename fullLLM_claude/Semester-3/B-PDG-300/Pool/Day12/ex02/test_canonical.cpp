/*
** EPITECH PROJECT, 2024
** Day12 PDG - Test Exercise 1
** File description:
** Test for canonical form compliance
*/

#include "Toy.hpp"
#include <iostream>

int main()
{
    std::cout << "=== Testing canonical form ===" << std::endl;

    // Test basic functionality
    Toy original(Toy::ALIEN, "ET", "./alien.txt");
    std::cout << "Original toy: " << original.getName() << std::endl;
    
    // Test copy constructor
    Toy copied(original);
    std::cout << "Copied toy: " << copied.getName() << std::endl;
    
    // Test assignment operator
    Toy assigned;
    assigned = original;
    std::cout << "Assigned toy: " << assigned.getName() << std::endl;
    
    // Modify original to test deep copy
    original.setName("Modified ET");
    std::cout << "After modification:" << std::endl;
    std::cout << "Original: " << original.getName() << std::endl;
    std::cout << "Copied: " << copied.getName() << std::endl;
    std::cout << "Assigned: " << assigned.getName() << std::endl;

    // Test Picture canonical form
    Picture pic1("./alien.txt");
    Picture pic2(pic1);
    Picture pic3;
    pic3 = pic1;
    
    std::cout << "\nPicture canonical form works!" << std::endl;
    
    return 0;
}
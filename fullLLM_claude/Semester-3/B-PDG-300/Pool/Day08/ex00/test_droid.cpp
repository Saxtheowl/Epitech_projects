/*
** EPITECH PROJECT, 2024
** Day08 PDG - Test Exercise 0
** File description:
** Test for Droid class
*/

#include "Droid.hpp"
#include <iostream>

int main()
{
    // Test constructors
    std::cout << "=== Constructor Tests ===" << std::endl;
    Droid droid1("R2-D2");
    Droid droid2;
    Droid droid3(droid1);

    std::cout << "Droid1 ID: " << droid1.getId() << std::endl;
    std::cout << "Droid1 Energy: " << droid1.getEnergy() << std::endl;
    std::cout << "Droid1 Attack: " << droid1.getAttack() << std::endl;
    std::cout << "Droid1 Toughness: " << droid1.getToughness() << std::endl;
    std::cout << "Droid1 Status: " << droid1.getStatus() << std::endl;

    // Test setters (Id has no setter - read-only)
    std::cout << "\n=== Setter Tests ===" << std::endl;
    droid2.setEnergy(75);
    droid2.setStatus("Activated");
    
    std::cout << "Droid2 ID: " << droid2.getId() << std::endl;
    std::cout << "Droid2 Energy: " << droid2.getEnergy() << std::endl;
    std::cout << "Droid2 Status: " << droid2.getStatus() << std::endl;

    // Test comparison operators
    std::cout << "\n=== Comparison Tests ===" << std::endl;
    std::cout << "Droid1 == Droid3: " << (droid1 == droid3 ? "true" : "false") << std::endl;
    std::cout << "Droid1 == Droid2: " << (droid1 == droid2 ? "true" : "false") << std::endl;
    std::cout << "Droid1 != Droid2: " << (droid1 != droid2 ? "true" : "false") << std::endl;

    // Test energy transfer/reload (from other Droid)
    std::cout << "\n=== Energy Transfer Tests ===" << std::endl;
    droid1.setEnergy(30);  // Set droid1 to low energy
    std::cout << "Droid1 Energy before transfer: " << droid1.getEnergy() << std::endl;
    std::cout << "Droid2 Energy before transfer: " << droid2.getEnergy() << std::endl;
    
    droid1 << droid2;  // Transfer energy from droid2 to droid1
    std::cout << "Droid1 Energy after transfer: " << droid1.getEnergy() << std::endl;
    std::cout << "Droid2 Energy after transfer: " << droid2.getEnergy() << std::endl;

    // Test assignment operator
    std::cout << "\n=== Assignment Tests ===" << std::endl;
    Droid droid4("BB-8");
    droid4 = droid1;
    std::cout << "Droid4 ID after assignment: " << droid4.getId() << std::endl;
    std::cout << "Droid4 Energy after assignment: " << droid4.getEnergy() << std::endl;

    return 0;
}
/*
** EPITECH PROJECT, 2024
** Day09 PDG - Exercise 3
** File description:
** Priest class implementation
*/

#include "Priest.hpp"

Priest::Priest(const std::string &name, int power) : Enchanter(name, power)
{
    std::cout << name << " enters in the order." << std::endl;
}

Priest::~Priest()
{
    std::cout << name << " finds peace." << std::endl;
}

void Priest::rest()
{
    if (hp == 0) {
        std::cout << name << " is out of combat." << std::endl;
        return;
    }
    
    power += 100;
    hp += 100;
    capValues();
    std::cout << name << " prays." << std::endl;
}
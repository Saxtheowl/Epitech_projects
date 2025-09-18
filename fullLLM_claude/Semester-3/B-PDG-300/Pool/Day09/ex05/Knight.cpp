/*
** EPITECH PROJECT, 2024
** Day09 PDG - Exercise 1
** File description:
** Knight class implementation
*/

#include "Knight.hpp"

Knight::Knight(const std::string &name, int power) : Peasant(name, power)
{
    std::cout << getName() << " vows to protect the kingdom." << std::endl;
}

Knight::~Knight()
{
    std::cout << getName() << " takes off his armor." << std::endl;
}

int Knight::attack()
{
    if (hp == 0) {
        std::cout << name << " is out of combat." << std::endl;
        return 0;
    }
    
    if (power < 10) {
        std::cout << name << " is out of power." << std::endl;
        return 0;
    }
    
    power -= 10;
    std::cout << name << " strikes with his sword." << std::endl;
    return 20;
}

int Knight::special()
{
    if (hp == 0) {
        std::cout << name << " is out of combat." << std::endl;
        return 0;
    }
    
    if (power < 30) {
        std::cout << name << " is out of power." << std::endl;
        return 0;
    }
    
    power -= 30;
    std::cout << name << " impales his enemy." << std::endl;
    return 50;
}

void Knight::rest()
{
    if (hp == 0) {
        std::cout << name << " is out of combat." << std::endl;
        return;
    }
    
    power += 50;
    capValues();
    std::cout << name << " eats." << std::endl;
}
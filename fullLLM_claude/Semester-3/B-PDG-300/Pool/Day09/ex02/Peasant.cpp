/*
** EPITECH PROJECT, 2024
** Day09 PDG - Exercise 0
** File description:
** Peasant class implementation
*/

#include "Peasant.hpp"

Peasant::Peasant(const std::string &name, int power) : name(name), power(power), hp(100)
{
    capValues();
    std::cout << name << " goes for an adventure." << std::endl;
}

Peasant::~Peasant()
{
    std::cout << name << " is back to his crops." << std::endl;
}

void Peasant::capValues()
{
    if (power < 0) power = 0;
    if (power > 100) power = 100;
    if (hp < 0) hp = 0;
    if (hp > 100) hp = 100;
}

const std::string& Peasant::getName() const
{
    return name;
}

int Peasant::getPower() const
{
    return power;
}

int Peasant::getHp() const
{
    return hp;
}

int Peasant::attack()
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
    std::cout << name << " tosses a stone." << std::endl;
    return 5;
}

int Peasant::special()
{
    if (hp == 0) {
        std::cout << name << " is out of combat." << std::endl;
        return 0;
    }
    
    std::cout << name << " doesn't know any special move." << std::endl;
    return 0;
}

void Peasant::rest()
{
    if (hp == 0) {
        std::cout << name << " is out of combat." << std::endl;
        return;
    }
    
    power += 30;
    capValues();
    std::cout << name << " takes a nap." << std::endl;
}

void Peasant::damage(int damage)
{
    std::cout << name << " takes " << damage << " damage." << std::endl;
    hp -= damage;
    if (hp <= 0) {
        hp = 0;
        std::cout << name << " is out of combat." << std::endl;
    }
}
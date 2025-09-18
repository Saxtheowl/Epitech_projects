/*
** EPITECH PROJECT, 2024
** Day09 PDG - Exercise 0
** File description:
** Peasant class header
*/

#ifndef PEASANT_HPP_
#define PEASANT_HPP_

#include <string>
#include <iostream>

class Peasant {
private:
    std::string name;
    int power;
    int hp;

    void capValues();

public:
    Peasant(const std::string &name, int power);
    ~Peasant();

    const std::string& getName() const;
    int getPower() const;
    int getHp() const;

    int attack();
    int special();
    void rest();
    void damage(int damage);
};

#endif /* !PEASANT_HPP_ */
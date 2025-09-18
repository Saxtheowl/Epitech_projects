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
#include "ICharacter.hpp"

class Peasant : virtual public ICharacter {
protected:
    std::string name;
    int power;
    int hp;

    void capValues();

public:
    Peasant(const std::string &name, int power);
    virtual ~Peasant();

    const std::string& getName() const;
    int getPower() const;
    int getHp() const;

    virtual int attack();
    virtual int special();
    virtual void rest();
    virtual void damage(int damage);
};

#endif /* !PEASANT_HPP_ */
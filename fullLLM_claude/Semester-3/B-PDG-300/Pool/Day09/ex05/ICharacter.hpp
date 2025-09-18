/*
** EPITECH PROJECT, 2024
** Day09 PDG - Exercise 5
** File description:
** Character Interface
*/

#ifndef ICHARACTER_HPP_
#define ICHARACTER_HPP_

#include <string>

class ICharacter {
public:
    virtual ~ICharacter() = default;
    
    // Combat methods
    virtual int attack() = 0;
    virtual int special() = 0;
    virtual void rest() = 0;
    virtual void damage(int damage) = 0;
    
    // Getter methods
    virtual const std::string& getName() const = 0;
    virtual int getHp() const = 0;
    virtual int getPower() const = 0;
};

#endif /* !ICHARACTER_HPP_ */
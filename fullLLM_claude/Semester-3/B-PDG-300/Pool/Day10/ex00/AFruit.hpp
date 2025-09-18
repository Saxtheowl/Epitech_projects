/*
** EPITECH PROJECT, 2024
** Day10 PDG - Exercise 0
** File description:
** AFruit abstract class - common implementation for all fruits
*/

#ifndef AFRUIT_HPP_
#define AFRUIT_HPP_

#include "IFruit.hpp"
#include <iostream>

class AFruit : public IFruit
{
protected:
    std::string name;
    unsigned int vitamins;
    bool peeled;

public:
    AFruit(const std::string& name, unsigned int vitamins);
    virtual ~AFruit() = default;

    std::string getName() const override;
    unsigned int getVitamins() const override;
    bool isPeeled() const override;
    void peel() override;
};

std::ostream& operator<<(std::ostream& os, const IFruit& fruit);

#endif /* !AFRUIT_HPP_ */
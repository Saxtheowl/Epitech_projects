/*
** EPITECH PROJECT, 2024
** Day10 PDG - Exercise 0
** File description:
** ABerry abstract class - for berries (always peeled)
*/

#ifndef ABERRY_HPP_
#define ABERRY_HPP_

#include "AFruit.hpp"

class ABerry : public AFruit
{
public:
    ABerry(const std::string& name, unsigned int vitamins);
    virtual ~ABerry() = default;

    // Override: berries are always peeled
    bool isPeeled() const override;
    void peel() override;
};

#endif /* !ABERRY_HPP_ */
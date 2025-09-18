/*
** EPITECH PROJECT, 2024
** Day09 PDG - Exercise 3
** File description:
** Priest class header
*/

#ifndef PRIEST_HPP_
#define PRIEST_HPP_

#include "Enchanter.hpp"

class Priest : public Enchanter {
public:
    Priest(const std::string &name, int power);
    ~Priest();

    void rest() override;
};

#endif /* !PRIEST_HPP_ */
/*
** EPITECH PROJECT, 2024
** Day09 PDG - Exercise 2
** File description:
** Enchanter class header
*/

#ifndef ENCHANTER_HPP_
#define ENCHANTER_HPP_

#include "Peasant.hpp"

class Enchanter : public Peasant {
public:
    Enchanter(const std::string &name, int power);
    ~Enchanter();

    int attack() override;
    int special() override;
    void rest() override;
};

#endif /* !ENCHANTER_HPP_ */
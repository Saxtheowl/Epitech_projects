/*
** EPITECH PROJECT, 2025
** Day08 - Droid
** File description:
** Droid class header
*/

#pragma once

#include <string>

class Droid {
private:
    std::string _id;
    std::size_t _energy;
    std::size_t _attack;
    std::size_t _toughness;
    std::string _status;

public:
    Droid();
    Droid(const std::string &id);
    Droid(const Droid &other);
    ~Droid();
    
    Droid &operator=(const Droid &other);
    bool operator==(const Droid &other) const;
    bool operator!=(const Droid &other) const;
    Droid &operator<<(std::size_t &energySource);

    // Getters
    std::string getId() const;
    std::size_t getEnergy() const;
    std::size_t getAttack() const;
    std::size_t getToughness() const;
    std::string getStatus() const;

    // Setters
    void setId(const std::string &id);
    void setEnergy(std::size_t energy);
    void setAttack(std::size_t attack);
    void setToughness(std::size_t toughness);
    void setStatus(const std::string &status);
};
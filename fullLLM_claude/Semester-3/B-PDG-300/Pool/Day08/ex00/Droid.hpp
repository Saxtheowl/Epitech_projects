/*
** EPITECH PROJECT, 2024
** Day08 PDG - Exercise 0
** File description:
** Droid class header
*/

#ifndef DROID_HPP_
#define DROID_HPP_

#include <string>
#include <iostream>

class Droid
{
private:
    std::string id;
    size_t energy;
    const size_t attack;
    const size_t toughness;
    std::string status;

public:
    // Constructors
    Droid(const std::string& id = "");
    Droid(const Droid& other);

    // Destructor
    ~Droid();

    // Assignment operator
    Droid& operator=(const Droid& other);

    // Getters
    const std::string& getId() const;
    size_t getEnergy() const;
    size_t getAttack() const;
    size_t getToughness() const;
    const std::string& getStatus() const;

    // Setters (only for non-const attributes, Id has no setter)
    void setEnergy(size_t energy);
    void setStatus(const std::string& status);

    // Comparison operators
    bool operator==(const Droid& other) const;
    bool operator!=(const Droid& other) const;

    // Stream operator (energy transfer from another Droid)
    Droid& operator<<(Droid& other);
};

#endif /* !DROID_HPP_ */
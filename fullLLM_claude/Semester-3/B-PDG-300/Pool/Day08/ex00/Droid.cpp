/*
** EPITECH PROJECT, 2024
** Day08 PDG - Exercise 0
** File description:
** Droid class implementation
*/

#include "Droid.hpp"

// Constructors
Droid::Droid(const std::string& id)
    : id(id), energy(50), attack(25), toughness(15), status("Standing by")
{
}

Droid::Droid(const Droid& other)
    : id(other.id), energy(other.energy), attack(other.attack), 
      toughness(other.toughness), status(other.status)
{
}

// Destructor
Droid::~Droid()
{
}

// Assignment operator
Droid& Droid::operator=(const Droid& other)
{
    if (this != &other) {
        id = other.id;
        energy = other.energy;
        // attack and toughness are const - they can't be reassigned after construction
        status = other.status;
    }
    return *this;
}

// Getters
const std::string& Droid::getId() const
{
    return id;
}

size_t Droid::getEnergy() const
{
    return energy;
}

size_t Droid::getAttack() const
{
    return attack;
}

size_t Droid::getToughness() const
{
    return toughness;
}

const std::string& Droid::getStatus() const
{
    return status;
}

// Setters (only for non-const attributes, Id has no setter)
void Droid::setEnergy(size_t energy)
{
    if (energy > 100)
        this->energy = 100;
    else
        this->energy = energy;
}

void Droid::setStatus(const std::string& status)
{
    this->status = status;
}

// Comparison operators
bool Droid::operator==(const Droid& other) const
{
    return (id == other.id && 
            energy == other.energy && 
            attack == other.attack && 
            toughness == other.toughness && 
            status == other.status);
}

bool Droid::operator!=(const Droid& other) const
{
    return !(*this == other);
}

// Stream operator (energy transfer/reload)
Droid& Droid::operator<<(Droid& other)
{
    size_t energyNeeded = 100 - energy;
    if (energyNeeded == 0)
        return *this;
    
    size_t energyTransfer = (other.energy >= energyNeeded) ? energyNeeded : other.energy;
    energy += energyTransfer;
    other.energy -= energyTransfer;
    
    return *this;
}
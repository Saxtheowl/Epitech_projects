/*
** EPITECH PROJECT, 2025
** Day08 - Droid
** File description:
** Droid class implementation
*/

#include "Droid.hpp"

Droid::Droid() : _id(""), _energy(50), _attack(25), _toughness(15), _status("Standing by")
{
}

Droid::Droid(const std::string &id) : _id(id), _energy(50), _attack(25), _toughness(15), _status("Standing by")
{
}

Droid::Droid(const Droid &other) : _id(other._id), _energy(other._energy), _attack(other._attack), 
                                   _toughness(other._toughness), _status(other._status)
{
}

Droid::~Droid()
{
}

Droid &Droid::operator=(const Droid &other)
{
    if (this != &other) {
        _id = other._id;
        _energy = other._energy;
        _attack = other._attack;
        _toughness = other._toughness;
        _status = other._status;
    }
    return *this;
}

bool Droid::operator==(const Droid &other) const
{
    return (_energy == other._energy && _attack == other._attack && 
            _toughness == other._toughness && _status == other._status);
}

bool Droid::operator!=(const Droid &other) const
{
    return !(*this == other);
}

Droid &Droid::operator<<(std::size_t &energySource)
{
    std::size_t needed = (100 > _energy) ? (100 - _energy) : 0;
    std::size_t toTransfer = (energySource > needed) ? needed : energySource;
    
    _energy += toTransfer;
    energySource -= toTransfer;
    
    return *this;
}

// Getters
std::string Droid::getId() const
{
    return _id;
}

std::size_t Droid::getEnergy() const
{
    return _energy;
}

std::size_t Droid::getAttack() const
{
    return _attack;
}

std::size_t Droid::getToughness() const
{
    return _toughness;
}

std::string Droid::getStatus() const
{
    return _status;
}

// Setters
void Droid::setId(const std::string &id)
{
    _id = id;
}

void Droid::setEnergy(std::size_t energy)
{
    if (energy <= 100) {
        _energy = energy;
    } else {
        _energy = 100;
    }
}

void Droid::setAttack(std::size_t attack)
{
    _attack = attack;
}

void Droid::setToughness(std::size_t toughness)
{
    _toughness = toughness;
}

void Droid::setStatus(const std::string &status)
{
    _status = status;
}
/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Abstract base class implementation
*/

#include "AComponent.hpp"
#include <stdexcept>

namespace nts {
    AComponent::AComponent(const std::string &name) : _currentTick(0), _name(name) {
    }

    void AComponent::simulate(std::size_t tick) {
        if (_currentTick < tick) {
            _currentTick = tick;
            // Update all output pins based on current inputs
            for (auto &pinPair : _pins) {
                if (isOutputPin(pinPair.first)) {
                    Tristate newValue = compute(pinPair.first);
                    setOutputValue(pinPair.first, newValue);
                }
            }
        }
    }

    void AComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) {
        if (!isPinValid(pin)) {
            throw std::invalid_argument("Invalid pin number: " + std::to_string(pin));
        }
        
        _pins[pin].component = &other;
        _pins[pin].pin = otherPin;
    }

    Tristate AComponent::getInputValue(std::size_t pin) {
        if (_pins.find(pin) == _pins.end() || !_pins[pin].component) {
            return Undefined;
        }
        
        return _pins[pin].component->compute(_pins[pin].pin);
    }

    void AComponent::setOutputValue(std::size_t pin, Tristate value) {
        if (_pins.find(pin) != _pins.end()) {
            _pins[pin].state = value;
        }
    }
}
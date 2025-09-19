/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Abstract component base class implementation
*/

#include "components/AComponent.hpp"

namespace nts {
    void AComponent::simulate(std::size_t tick) {
        if (_currentTick != tick) {
            _currentTick = tick;
            updateOutputs();
        }
    }

    void AComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) {
        _pins[pin].component = &other;
        _pins[pin].otherPin = otherPin;
    }

    nts::Tristate AComponent::getInputValue(std::size_t pin) {
        if (_pins.find(pin) == _pins.end() || !_pins[pin].component) {
            return Tristate::Undefined;
        }

        return _pins[pin].component->compute(_pins[pin].otherPin);
    }

    void AComponent::setOutputValue(std::size_t pin, nts::Tristate value) {
        _pins[pin].value = value;
    }

    bool AComponent::hasLink(std::size_t pin) const {
        auto it = _pins.find(pin);
        return it != _pins.end() && it->second.component != nullptr;
    }

    nts::Tristate AComponent::compute(std::size_t pin) {
        auto it = _pins.find(pin);
        if (it == _pins.end()) {
            return Tristate::Undefined;
        }
        return it->second.value;
    }
}
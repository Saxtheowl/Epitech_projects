/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Special components implementation
*/

#include "Components.hpp"

namespace nts {
    // InputComponent
    InputComponent::InputComponent(const std::string &name) 
        : AComponent(name), _value(Undefined) {
    }

    Tristate InputComponent::compute(std::size_t pin) {
        if (pin != 1) return Undefined;
        return _value;
    }

    bool InputComponent::isPinValid(std::size_t pin) const {
        return pin == 1;
    }

    bool InputComponent::isInputPin(std::size_t pin) const {
        (void)pin;
        return false; // Input component has no input pins
    }

    bool InputComponent::isOutputPin(std::size_t pin) const {
        return pin == 1;
    }

    void InputComponent::setValue(Tristate value) {
        _value = value;
    }

    // OutputComponent
    OutputComponent::OutputComponent(const std::string &name) : AComponent(name) {
    }

    Tristate OutputComponent::compute(std::size_t pin) {
        if (pin != 1) return Undefined;
        return getInputValue(1);
    }

    bool OutputComponent::isPinValid(std::size_t pin) const {
        return pin == 1;
    }

    bool OutputComponent::isInputPin(std::size_t pin) const {
        return pin == 1;
    }

    bool OutputComponent::isOutputPin(std::size_t pin) const {
        (void)pin;
        return false; // Output component has no output pins (it's a sink)
    }

    // TrueComponent
    TrueComponent::TrueComponent(const std::string &name) : AComponent(name) {
    }

    Tristate TrueComponent::compute(std::size_t pin) {
        if (pin != 1) return Undefined;
        return True;
    }

    bool TrueComponent::isPinValid(std::size_t pin) const {
        return pin == 1;
    }

    bool TrueComponent::isInputPin(std::size_t pin) const {
        (void)pin;
        return false;
    }

    bool TrueComponent::isOutputPin(std::size_t pin) const {
        return pin == 1;
    }

    // FalseComponent
    FalseComponent::FalseComponent(const std::string &name) : AComponent(name) {
    }

    Tristate FalseComponent::compute(std::size_t pin) {
        if (pin != 1) return Undefined;
        return False;
    }

    bool FalseComponent::isPinValid(std::size_t pin) const {
        return pin == 1;
    }

    bool FalseComponent::isInputPin(std::size_t pin) const {
        (void)pin;
        return false;
    }

    bool FalseComponent::isOutputPin(std::size_t pin) const {
        return pin == 1;
    }

    // ClockComponent
    ClockComponent::ClockComponent(const std::string &name) 
        : AComponent(name), _value(Undefined), _lastTick(0) {
    }

    void ClockComponent::simulate(std::size_t tick) {
        if (tick > _lastTick && _value != Undefined) {
            _value = (_value == True) ? False : True;
        }
        _lastTick = tick;
        AComponent::simulate(tick);
    }

    Tristate ClockComponent::compute(std::size_t pin) {
        if (pin != 1) return Undefined;
        return _value;
    }

    bool ClockComponent::isPinValid(std::size_t pin) const {
        return pin == 1;
    }

    bool ClockComponent::isInputPin(std::size_t pin) const {
        (void)pin;
        return false;
    }

    bool ClockComponent::isOutputPin(std::size_t pin) const {
        return pin == 1;
    }

    void ClockComponent::setValue(Tristate value) {
        _value = value;
    }
}
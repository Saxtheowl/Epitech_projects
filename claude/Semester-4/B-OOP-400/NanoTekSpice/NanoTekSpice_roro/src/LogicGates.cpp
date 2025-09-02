/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Logic gates implementation
*/

#include "Components.hpp"

namespace nts {
    // Helper functions for logic operations with Undefined state
    static Tristate andOperation(Tristate a, Tristate b) {
        if (a == False || b == False) return False;
        if (a == True && b == True) return True;
        return Undefined;
    }

    static Tristate orOperation(Tristate a, Tristate b) {
        if (a == True || b == True) return True;
        if (a == False && b == False) return False;
        return Undefined;
    }

    static Tristate xorOperation(Tristate a, Tristate b) {
        if (a == Undefined || b == Undefined) return Undefined;
        if (a != b) return True;
        return False;
    }

    static Tristate notOperation(Tristate a) {
        if (a == True) return False;
        if (a == False) return True;
        return Undefined;
    }

    // AndGate
    AndGate::AndGate(const std::string &name) : AComponent(name) {
    }

    Tristate AndGate::compute(std::size_t pin) {
        if (pin == 3) { // Output pin
            Tristate a = getInputValue(1);
            Tristate b = getInputValue(2);
            return andOperation(a, b);
        }
        return Undefined;
    }

    bool AndGate::isPinValid(std::size_t pin) const {
        return pin >= 1 && pin <= 3;
    }

    bool AndGate::isInputPin(std::size_t pin) const {
        return pin == 1 || pin == 2;
    }

    bool AndGate::isOutputPin(std::size_t pin) const {
        return pin == 3;
    }

    // OrGate
    OrGate::OrGate(const std::string &name) : AComponent(name) {
    }

    Tristate OrGate::compute(std::size_t pin) {
        if (pin == 3) { // Output pin
            Tristate a = getInputValue(1);
            Tristate b = getInputValue(2);
            return orOperation(a, b);
        }
        return Undefined;
    }

    bool OrGate::isPinValid(std::size_t pin) const {
        return pin >= 1 && pin <= 3;
    }

    bool OrGate::isInputPin(std::size_t pin) const {
        return pin == 1 || pin == 2;
    }

    bool OrGate::isOutputPin(std::size_t pin) const {
        return pin == 3;
    }

    // XorGate
    XorGate::XorGate(const std::string &name) : AComponent(name) {
    }

    Tristate XorGate::compute(std::size_t pin) {
        if (pin == 3) { // Output pin
            Tristate a = getInputValue(1);
            Tristate b = getInputValue(2);
            return xorOperation(a, b);
        }
        return Undefined;
    }

    bool XorGate::isPinValid(std::size_t pin) const {
        return pin >= 1 && pin <= 3;
    }

    bool XorGate::isInputPin(std::size_t pin) const {
        return pin == 1 || pin == 2;
    }

    bool XorGate::isOutputPin(std::size_t pin) const {
        return pin == 3;
    }

    // NotGate
    NotGate::NotGate(const std::string &name) : AComponent(name) {
    }

    Tristate NotGate::compute(std::size_t pin) {
        if (pin == 2) { // Output pin
            Tristate a = getInputValue(1);
            return notOperation(a);
        }
        return Undefined;
    }

    bool NotGate::isPinValid(std::size_t pin) const {
        return pin == 1 || pin == 2;
    }

    bool NotGate::isInputPin(std::size_t pin) const {
        return pin == 1;
    }

    bool NotGate::isOutputPin(std::size_t pin) const {
        return pin == 2;
    }

    // Chip4081 - Four AND gates
    Chip4081::Chip4081(const std::string &name) : AComponent(name) {
    }

    Tristate Chip4081::compute(std::size_t pin) {
        switch (pin) {
            case 3:  // Gate 1 output
                return andOperation(getInputValue(1), getInputValue(2));
            case 4:  // Gate 2 output
                return andOperation(getInputValue(5), getInputValue(6));
            case 10: // Gate 3 output
                return andOperation(getInputValue(8), getInputValue(9));
            case 11: // Gate 4 output
                return andOperation(getInputValue(12), getInputValue(13));
        }
        return Undefined;
    }

    bool Chip4081::isPinValid(std::size_t pin) const {
        return (pin >= 1 && pin <= 6) || (pin >= 8 && pin <= 13);
    }

    bool Chip4081::isInputPin(std::size_t pin) const {
        return pin == 1 || pin == 2 || pin == 5 || pin == 6 || 
               pin == 8 || pin == 9 || pin == 12 || pin == 13;
    }

    bool Chip4081::isOutputPin(std::size_t pin) const {
        return pin == 3 || pin == 4 || pin == 10 || pin == 11;
    }

    // Chip4071 - Four OR gates
    Chip4071::Chip4071(const std::string &name) : AComponent(name) {
    }

    Tristate Chip4071::compute(std::size_t pin) {
        switch (pin) {
            case 3:  // Gate 1 output
                return orOperation(getInputValue(1), getInputValue(2));
            case 4:  // Gate 2 output
                return orOperation(getInputValue(5), getInputValue(6));
            case 10: // Gate 3 output
                return orOperation(getInputValue(8), getInputValue(9));
            case 11: // Gate 4 output
                return orOperation(getInputValue(12), getInputValue(13));
        }
        return Undefined;
    }

    bool Chip4071::isPinValid(std::size_t pin) const {
        return (pin >= 1 && pin <= 6) || (pin >= 8 && pin <= 13);
    }

    bool Chip4071::isInputPin(std::size_t pin) const {
        return pin == 1 || pin == 2 || pin == 5 || pin == 6 || 
               pin == 8 || pin == 9 || pin == 12 || pin == 13;
    }

    bool Chip4071::isOutputPin(std::size_t pin) const {
        return pin == 3 || pin == 4 || pin == 10 || pin == 11;
    }
}
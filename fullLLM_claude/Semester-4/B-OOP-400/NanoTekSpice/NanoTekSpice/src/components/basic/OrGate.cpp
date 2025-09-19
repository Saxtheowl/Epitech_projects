/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** OR gate component implementation
*/

#include "components/basic/OrGate.hpp"

namespace nts {
    OrGate::OrGate() {
        // Pin 1 and 2 are inputs, pin 3 is output
        _pins[1] = Pin{};
        _pins[2] = Pin{};
        _pins[3] = Pin{};
    }

    void OrGate::updateOutputs() {
        nts::Tristate input1 = getInputValue(1);
        nts::Tristate input2 = getInputValue(2);
        nts::Tristate result = computeOr(input1, input2);
        setOutputValue(3, result);
    }

    nts::Tristate OrGate::computeOr(nts::Tristate a, nts::Tristate b) {
        if (a == Tristate::True || b == Tristate::True) {
            return Tristate::True;
        }
        if (a == Tristate::False && b == Tristate::False) {
            return Tristate::False;
        }
        return Tristate::Undefined;
    }
}
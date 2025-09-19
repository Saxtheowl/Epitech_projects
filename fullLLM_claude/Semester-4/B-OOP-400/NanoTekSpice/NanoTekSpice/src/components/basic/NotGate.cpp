/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** NOT gate component implementation
*/

#include "components/basic/NotGate.hpp"

namespace nts {
    NotGate::NotGate() {
        // Pin 1 is input, pin 2 is output
        _pins[1] = Pin{};
        _pins[2] = Pin{};
    }

    void NotGate::updateOutputs() {
        nts::Tristate input = getInputValue(1);
        nts::Tristate result = computeNot(input);
        setOutputValue(2, result);
    }

    nts::Tristate NotGate::computeNot(nts::Tristate a) {
        if (a == Tristate::True) {
            return Tristate::False;
        }
        if (a == Tristate::False) {
            return Tristate::True;
        }
        return Tristate::Undefined;
    }
}
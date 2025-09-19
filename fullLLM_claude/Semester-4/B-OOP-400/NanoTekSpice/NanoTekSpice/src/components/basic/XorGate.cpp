/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** XOR gate component implementation
*/

#include "components/basic/XorGate.hpp"

namespace nts {
    XorGate::XorGate() {
        // Pin 1 and 2 are inputs, pin 3 is output
        _pins[1] = Pin{};
        _pins[2] = Pin{};
        _pins[3] = Pin{};
    }

    void XorGate::updateOutputs() {
        nts::Tristate input1 = getInputValue(1);
        nts::Tristate input2 = getInputValue(2);
        nts::Tristate result = computeXor(input1, input2);
        setOutputValue(3, result);
    }

    nts::Tristate XorGate::computeXor(nts::Tristate a, nts::Tristate b) {
        if (a == Tristate::Undefined || b == Tristate::Undefined) {
            return Tristate::Undefined;
        }
        if ((a == Tristate::True && b == Tristate::False) ||
            (a == Tristate::False && b == Tristate::True)) {
            return Tristate::True;
        }
        return Tristate::False;
    }
}
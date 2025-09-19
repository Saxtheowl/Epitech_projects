/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Output component implementation
*/

#include "components/basic/Output.hpp"

namespace nts {
    Output::Output() {
        // Pin 1 is the input
        _pins[1] = Pin{};
    }

    nts::Tristate Output::compute(std::size_t pin) {
        if (pin != 1) {
            return Tristate::Undefined;
        }
        return getInputValue(1);
    }

    void Output::updateOutputs() {
        // Output components don't have outputs to update
        // The value is computed on demand through getInputValue
    }
}
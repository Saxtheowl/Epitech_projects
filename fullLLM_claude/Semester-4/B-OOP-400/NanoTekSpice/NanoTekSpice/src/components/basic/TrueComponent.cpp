/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** True component implementation
*/

#include "components/basic/TrueComponent.hpp"

namespace nts {
    TrueComponent::TrueComponent() {
        // Pin 1 is the output
        _pins[1] = Pin{};
    }

    nts::Tristate TrueComponent::compute(std::size_t pin) {
        if (pin != 1) {
            return Tristate::Undefined;
        }
        return Tristate::True;
    }

    void TrueComponent::updateOutputs() {
        setOutputValue(1, Tristate::True);
    }
}
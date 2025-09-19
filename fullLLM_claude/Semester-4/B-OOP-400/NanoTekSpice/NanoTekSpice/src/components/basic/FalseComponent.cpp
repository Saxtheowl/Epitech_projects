/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** False component implementation
*/

#include "components/basic/FalseComponent.hpp"

namespace nts {
    FalseComponent::FalseComponent() {
        // Pin 1 is the output
        _pins[1] = Pin{};
    }

    nts::Tristate FalseComponent::compute(std::size_t pin) {
        if (pin != 1) {
            return Tristate::Undefined;
        }
        return Tristate::False;
    }

    void FalseComponent::updateOutputs() {
        setOutputValue(1, Tristate::False);
    }
}
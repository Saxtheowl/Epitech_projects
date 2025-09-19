/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Input component implementation
*/

#include "components/basic/Input.hpp"

namespace nts {
    Input::Input() {
        // Pin 1 is the output
        _pins[1] = Pin{};
    }

    nts::Tristate Input::compute(std::size_t pin) {
        if (pin != 1) {
            return Tristate::Undefined;
        }
        return _state;
    }

    void Input::setState(nts::Tristate state) {
        _state = state;
    }

    void Input::updateOutputs() {
        setOutputValue(1, _state);
    }
}
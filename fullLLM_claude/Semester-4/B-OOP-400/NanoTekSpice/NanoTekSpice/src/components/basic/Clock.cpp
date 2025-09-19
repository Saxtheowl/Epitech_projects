/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Clock component implementation
*/

#include "components/basic/Clock.hpp"

namespace nts {
    Clock::Clock() {
        // Pin 1 is the output
        _pins[1] = Pin{};
    }

    nts::Tristate Clock::compute(std::size_t pin) {
        if (pin != 1) {
            return Tristate::Undefined;
        }
        return _state;
    }

    void Clock::setState(nts::Tristate state) {
        _state = state;
    }

    void Clock::simulate(std::size_t tick) {
        if (_currentTick != tick) {
            _currentTick = tick;
            // Clock inverts its state after each simulation
            if (_state == Tristate::True) {
                _state = Tristate::False;
            } else if (_state == Tristate::False) {
                _state = Tristate::True;
            }
            updateOutputs();
        }
    }

    void Clock::updateOutputs() {
        setOutputValue(1, _state);
    }
}
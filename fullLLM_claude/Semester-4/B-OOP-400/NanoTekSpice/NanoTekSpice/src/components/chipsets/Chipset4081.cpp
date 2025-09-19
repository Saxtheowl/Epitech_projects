/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** 4081 chipset implementation - Four AND gates
*/

#include "components/chipsets/Chipset4081.hpp"

namespace nts {
    Chipset4081::Chipset4081() {
        // Initialize all pins according to 4081 pinout
        // Pin 1,2 -> Gate 1 inputs, Pin 3 -> Gate 1 output
        // Pin 4 -> Gate 2 output, Pin 5,6 -> Gate 2 inputs
        // Pin 7 -> VSS (ignored), Pin 8,9 -> Gate 3 inputs
        // Pin 10 -> Gate 3 output, Pin 11 -> Gate 4 output
        // Pin 12,13 -> Gate 4 inputs, Pin 14 -> VDD (ignored)

        for (int i = 1; i <= 14; ++i) {
            if (i != 7 && i != 14) { // Skip VSS and VDD
                _pins[i] = Pin{};
            }
        }
    }

    void Chipset4081::updateOutputs() {
        // Gate 1: pins 1,2 -> pin 3
        nts::Tristate gate1_out = computeAnd(getInputValue(1), getInputValue(2));
        setOutputValue(3, gate1_out);

        // Gate 2: pins 5,6 -> pin 4
        nts::Tristate gate2_out = computeAnd(getInputValue(5), getInputValue(6));
        setOutputValue(4, gate2_out);

        // Gate 3: pins 8,9 -> pin 10
        nts::Tristate gate3_out = computeAnd(getInputValue(8), getInputValue(9));
        setOutputValue(10, gate3_out);

        // Gate 4: pins 12,13 -> pin 11
        nts::Tristate gate4_out = computeAnd(getInputValue(12), getInputValue(13));
        setOutputValue(11, gate4_out);
    }

    nts::Tristate Chipset4081::computeAnd(nts::Tristate a, nts::Tristate b) {
        if (a == Tristate::False || b == Tristate::False) {
            return Tristate::False;
        }
        if (a == Tristate::True && b == Tristate::True) {
            return Tristate::True;
        }
        return Tristate::Undefined;
    }
}
/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** 4071 chipset implementation - Four OR gates
*/

#include "components/chipsets/Chipset4071.hpp"

namespace nts {
    Chipset4071::Chipset4071() {
        // Initialize all pins according to 4071 pinout (same as 4081)
        for (int i = 1; i <= 14; ++i) {
            if (i != 7 && i != 14) { // Skip VSS and VDD
                _pins[i] = Pin{};
            }
        }
    }

    void Chipset4071::updateOutputs() {
        // Gate 1: pins 1,2 -> pin 3
        nts::Tristate gate1_out = computeOr(getInputValue(1), getInputValue(2));
        setOutputValue(3, gate1_out);

        // Gate 2: pins 5,6 -> pin 4
        nts::Tristate gate2_out = computeOr(getInputValue(5), getInputValue(6));
        setOutputValue(4, gate2_out);

        // Gate 3: pins 8,9 -> pin 10
        nts::Tristate gate3_out = computeOr(getInputValue(8), getInputValue(9));
        setOutputValue(10, gate3_out);

        // Gate 4: pins 12,13 -> pin 11
        nts::Tristate gate4_out = computeOr(getInputValue(12), getInputValue(13));
        setOutputValue(11, gate4_out);
    }

    nts::Tristate Chipset4071::computeOr(nts::Tristate a, nts::Tristate b) {
        if (a == Tristate::True || b == Tristate::True) {
            return Tristate::True;
        }
        if (a == Tristate::False && b == Tristate::False) {
            return Tristate::False;
        }
        return Tristate::Undefined;
    }
}
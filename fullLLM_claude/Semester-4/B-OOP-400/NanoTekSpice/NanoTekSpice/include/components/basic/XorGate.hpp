/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** XOR gate component
*/

#pragma once

#include "components/AComponent.hpp"

namespace nts {
    class XorGate : public AComponent {
    public:
        XorGate();
        ~XorGate() = default;

    protected:
        void updateOutputs() override;

    private:
        nts::Tristate computeXor(nts::Tristate a, nts::Tristate b);
    };
}
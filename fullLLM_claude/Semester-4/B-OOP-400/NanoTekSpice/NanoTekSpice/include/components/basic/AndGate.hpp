/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** AND gate component
*/

#pragma once

#include "components/AComponent.hpp"

namespace nts {
    class AndGate : public AComponent {
    public:
        AndGate();
        ~AndGate() = default;

    protected:
        void updateOutputs() override;

    private:
        nts::Tristate computeAnd(nts::Tristate a, nts::Tristate b);
    };
}
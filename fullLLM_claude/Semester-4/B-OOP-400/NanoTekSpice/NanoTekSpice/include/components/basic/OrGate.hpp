/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** OR gate component
*/

#pragma once

#include "components/AComponent.hpp"

namespace nts {
    class OrGate : public AComponent {
    public:
        OrGate();
        ~OrGate() = default;

    protected:
        void updateOutputs() override;

    private:
        nts::Tristate computeOr(nts::Tristate a, nts::Tristate b);
    };
}
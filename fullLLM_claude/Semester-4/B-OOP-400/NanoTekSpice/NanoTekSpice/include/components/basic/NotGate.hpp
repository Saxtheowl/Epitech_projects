/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** NOT gate component
*/

#pragma once

#include "components/AComponent.hpp"

namespace nts {
    class NotGate : public AComponent {
    public:
        NotGate();
        ~NotGate() = default;

    protected:
        void updateOutputs() override;

    private:
        nts::Tristate computeNot(nts::Tristate a);
    };
}
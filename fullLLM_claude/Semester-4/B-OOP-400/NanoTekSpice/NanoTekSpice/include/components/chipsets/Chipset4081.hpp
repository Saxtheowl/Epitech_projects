/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** 4081 chipset - Four AND gates
*/

#pragma once

#include "components/AComponent.hpp"

namespace nts {
    class Chipset4081 : public AComponent {
    public:
        Chipset4081();
        ~Chipset4081() = default;

    protected:
        void updateOutputs() override;

    private:
        nts::Tristate computeAnd(nts::Tristate a, nts::Tristate b);
    };
}
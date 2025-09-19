/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** 4071 chipset - Four OR gates
*/

#pragma once

#include "components/AComponent.hpp"

namespace nts {
    class Chipset4071 : public AComponent {
    public:
        Chipset4071();
        ~Chipset4071() = default;

    protected:
        void updateOutputs() override;

    private:
        nts::Tristate computeOr(nts::Tristate a, nts::Tristate b);
    };
}
/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Output component
*/

#pragma once

#include "components/AComponent.hpp"

namespace nts {
    class Output : public AComponent {
    public:
        Output();
        ~Output() = default;

        nts::Tristate compute(std::size_t pin) override;

    protected:
        void updateOutputs() override;
    };
}
/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** False component (always outputs false)
*/

#pragma once

#include "components/AComponent.hpp"

namespace nts {
    class FalseComponent : public AComponent {
    public:
        FalseComponent();
        ~FalseComponent() = default;

        nts::Tristate compute(std::size_t pin) override;

    protected:
        void updateOutputs() override;
    };
}
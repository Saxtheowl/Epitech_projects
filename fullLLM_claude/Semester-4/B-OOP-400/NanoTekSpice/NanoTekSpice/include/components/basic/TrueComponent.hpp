/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** True component (always outputs true)
*/

#pragma once

#include "components/AComponent.hpp"

namespace nts {
    class TrueComponent : public AComponent {
    public:
        TrueComponent();
        ~TrueComponent() = default;

        nts::Tristate compute(std::size_t pin) override;

    protected:
        void updateOutputs() override;
    };
}
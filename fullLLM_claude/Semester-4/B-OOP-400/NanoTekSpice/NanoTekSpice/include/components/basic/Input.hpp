/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Input component
*/

#pragma once

#include "components/AComponent.hpp"

namespace nts {
    class Input : public AComponent {
    private:
        nts::Tristate _state = Tristate::Undefined;

    public:
        Input();
        ~Input() = default;

        nts::Tristate compute(std::size_t pin) override;
        void setState(nts::Tristate state);

    protected:
        void updateOutputs() override;
    };
}
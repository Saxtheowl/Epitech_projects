/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Clock component
*/

#pragma once

#include "components/AComponent.hpp"

namespace nts {
    class Clock : public AComponent {
    private:
        nts::Tristate _state = Tristate::Undefined;

    public:
        Clock();
        ~Clock() = default;

        nts::Tristate compute(std::size_t pin) override;
        void setState(nts::Tristate state);
        void simulate(std::size_t tick) override;

    protected:
        void updateOutputs() override;
    };
}
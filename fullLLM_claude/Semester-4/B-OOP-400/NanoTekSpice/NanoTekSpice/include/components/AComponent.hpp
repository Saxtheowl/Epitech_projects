/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Abstract component base class
*/

#pragma once

#include "nts/IComponent.hpp"
#include <map>
#include <memory>

namespace nts {
    class AComponent : public IComponent {
    protected:
        struct Pin {
            nts::IComponent *component = nullptr;
            std::size_t otherPin = 0;
            nts::Tristate value = Tristate::Undefined;
        };

        std::map<std::size_t, Pin> _pins;
        std::size_t _currentTick = 0;

    public:
        virtual ~AComponent() = default;

        void simulate(std::size_t tick) override;
        nts::Tristate compute(std::size_t pin) override;
        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;

    protected:
        nts::Tristate getInputValue(std::size_t pin);
        void setOutputValue(std::size_t pin, nts::Tristate value);
        bool hasLink(std::size_t pin) const;
        virtual void updateOutputs() = 0;
    };
}
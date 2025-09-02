/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** All component classes declaration
*/

#ifndef COMPONENTS_HPP_
#define COMPONENTS_HPP_

#include "AComponent.hpp"

namespace nts {
    // Special components
    class InputComponent : public AComponent {
    public:
        InputComponent(const std::string &name = "");
        Tristate compute(std::size_t pin) override;
        bool isPinValid(std::size_t pin) const override;
        bool isInputPin(std::size_t pin) const override;
        bool isOutputPin(std::size_t pin) const override;
        void setValue(Tristate value);
    private:
        Tristate _value;
    };

    class OutputComponent : public AComponent {
    public:
        OutputComponent(const std::string &name = "");
        Tristate compute(std::size_t pin) override;
        bool isPinValid(std::size_t pin) const override;
        bool isInputPin(std::size_t pin) const override;
        bool isOutputPin(std::size_t pin) const override;
    };

    class TrueComponent : public AComponent {
    public:
        TrueComponent(const std::string &name = "");
        Tristate compute(std::size_t pin) override;
        bool isPinValid(std::size_t pin) const override;
        bool isInputPin(std::size_t pin) const override;
        bool isOutputPin(std::size_t pin) const override;
    };

    class FalseComponent : public AComponent {
    public:
        FalseComponent(const std::string &name = "");
        Tristate compute(std::size_t pin) override;
        bool isPinValid(std::size_t pin) const override;
        bool isInputPin(std::size_t pin) const override;
        bool isOutputPin(std::size_t pin) const override;
    };

    class ClockComponent : public AComponent {
    public:
        ClockComponent(const std::string &name = "");
        void simulate(std::size_t tick) override;
        Tristate compute(std::size_t pin) override;
        bool isPinValid(std::size_t pin) const override;
        bool isInputPin(std::size_t pin) const override;
        bool isOutputPin(std::size_t pin) const override;
        void setValue(Tristate value);
    private:
        Tristate _value;
        std::size_t _lastTick;
    };

    // Elementary gates
    class AndGate : public AComponent {
    public:
        AndGate(const std::string &name = "");
        Tristate compute(std::size_t pin) override;
        bool isPinValid(std::size_t pin) const override;
        bool isInputPin(std::size_t pin) const override;
        bool isOutputPin(std::size_t pin) const override;
    };

    class OrGate : public AComponent {
    public:
        OrGate(const std::string &name = "");
        Tristate compute(std::size_t pin) override;
        bool isPinValid(std::size_t pin) const override;
        bool isInputPin(std::size_t pin) const override;
        bool isOutputPin(std::size_t pin) const override;
    };

    class XorGate : public AComponent {
    public:
        XorGate(const std::string &name = "");
        Tristate compute(std::size_t pin) override;
        bool isPinValid(std::size_t pin) const override;
        bool isInputPin(std::size_t pin) const override;
        bool isOutputPin(std::size_t pin) const override;
    };

    class NotGate : public AComponent {
    public:
        NotGate(const std::string &name = "");
        Tristate compute(std::size_t pin) override;
        bool isPinValid(std::size_t pin) const override;
        bool isInputPin(std::size_t pin) const override;
        bool isOutputPin(std::size_t pin) const override;
    };

    // Chip 4081 - Four AND gates
    class Chip4081 : public AComponent {
    public:
        Chip4081(const std::string &name = "");
        Tristate compute(std::size_t pin) override;
        bool isPinValid(std::size_t pin) const override;
        bool isInputPin(std::size_t pin) const override;
        bool isOutputPin(std::size_t pin) const override;
    };

    // Chip 4071 - Four OR gates
    class Chip4071 : public AComponent {
    public:
        Chip4071(const std::string &name = "");
        Tristate compute(std::size_t pin) override;
        bool isPinValid(std::size_t pin) const override;
        bool isInputPin(std::size_t pin) const override;
        bool isOutputPin(std::size_t pin) const override;
    };
}

#endif /* !COMPONENTS_HPP_ */
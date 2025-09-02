/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Abstract base class for components
*/

#ifndef ACOMPONENT_HPP_
#define ACOMPONENT_HPP_

#include "IComponent.hpp"
#include <vector>
#include <map>
#include <string>

namespace nts {
    struct Pin {
        IComponent *component;
        std::size_t pin;
        Tristate state;
        
        Pin() : component(nullptr), pin(0), state(Undefined) {}
    };

    class AComponent : public IComponent {
    protected:
        std::map<std::size_t, Pin> _pins;
        std::size_t _currentTick;
        std::string _name;

    public:
        AComponent(const std::string &name = "");
        virtual ~AComponent() = default;

        void simulate(std::size_t tick) override;
        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;
        
        const std::string &getName() const { return _name; }
        void setName(const std::string &name) { _name = name; }
        
        // Helper methods
        virtual bool isPinValid(std::size_t pin) const = 0;
        virtual bool isInputPin(std::size_t pin) const = 0;
        virtual bool isOutputPin(std::size_t pin) const = 0;

    protected:
        Tristate getInputValue(std::size_t pin);
        void setOutputValue(std::size_t pin, Tristate value);
    };
}

#endif /* !ACOMPONENT_HPP_ */
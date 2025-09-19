/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Factory for creating components implementation
*/

#include "core/ComponentFactory.hpp"
#include "components/basic/Input.hpp"
#include "components/basic/Output.hpp"
#include "components/basic/TrueComponent.hpp"
#include "components/basic/FalseComponent.hpp"
#include "components/basic/Clock.hpp"
#include "components/basic/AndGate.hpp"
#include "components/basic/OrGate.hpp"
#include "components/basic/XorGate.hpp"
#include "components/basic/NotGate.hpp"
#include "components/chipsets/Chipset4081.hpp"
#include "components/chipsets/Chipset4071.hpp"

namespace nts {
    ComponentFactory::ComponentFactory() {
        _creators["input"] = [this]() { return createInput(); };
        _creators["output"] = [this]() { return createOutput(); };
        _creators["true"] = [this]() { return createTrue(); };
        _creators["false"] = [this]() { return createFalse(); };
        _creators["clock"] = [this]() { return createClock(); };
        _creators["and"] = [this]() { return createAnd(); };
        _creators["or"] = [this]() { return createOr(); };
        _creators["xor"] = [this]() { return createXor(); };
        _creators["not"] = [this]() { return createNot(); };
        _creators["4001"] = [this]() { return create4001(); };
        _creators["4011"] = [this]() { return create4011(); };
        _creators["4030"] = [this]() { return create4030(); };
        _creators["4069"] = [this]() { return create4069(); };
        _creators["4071"] = [this]() { return create4071(); };
        _creators["4081"] = [this]() { return create4081(); };
    }

    std::unique_ptr<nts::IComponent> ComponentFactory::createComponent(const std::string &type) {
        auto it = _creators.find(type);
        if (it != _creators.end()) {
            return it->second();
        }
        return nullptr;
    }

    std::unique_ptr<nts::IComponent> ComponentFactory::createInput() const {
        return std::make_unique<Input>();
    }

    std::unique_ptr<nts::IComponent> ComponentFactory::createOutput() const {
        return std::make_unique<Output>();
    }

    std::unique_ptr<nts::IComponent> ComponentFactory::createTrue() const {
        return std::make_unique<TrueComponent>();
    }

    std::unique_ptr<nts::IComponent> ComponentFactory::createFalse() const {
        return std::make_unique<FalseComponent>();
    }

    std::unique_ptr<nts::IComponent> ComponentFactory::createClock() const {
        return std::make_unique<Clock>();
    }

    std::unique_ptr<nts::IComponent> ComponentFactory::createAnd() const {
        return std::make_unique<AndGate>();
    }

    std::unique_ptr<nts::IComponent> ComponentFactory::createOr() const {
        return std::make_unique<OrGate>();
    }

    std::unique_ptr<nts::IComponent> ComponentFactory::createXor() const {
        return std::make_unique<XorGate>();
    }

    std::unique_ptr<nts::IComponent> ComponentFactory::createNot() const {
        return std::make_unique<NotGate>();
    }

    // TODO: Implement chipset components
    std::unique_ptr<nts::IComponent> ComponentFactory::create4001() const {
        return nullptr; // NOR gates
    }

    std::unique_ptr<nts::IComponent> ComponentFactory::create4011() const {
        return nullptr; // NAND gates
    }

    std::unique_ptr<nts::IComponent> ComponentFactory::create4030() const {
        return nullptr; // XOR gates
    }

    std::unique_ptr<nts::IComponent> ComponentFactory::create4069() const {
        return nullptr; // INVERTER gates
    }

    std::unique_ptr<nts::IComponent> ComponentFactory::create4071() const {
        return std::make_unique<Chipset4071>();
    }

    std::unique_ptr<nts::IComponent> ComponentFactory::create4081() const {
        return std::make_unique<Chipset4081>();
    }
}
/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Component factory implementation
*/

#include "ComponentFactory.hpp"
#include "Components.hpp"
#include <stdexcept>

namespace nts {
    ComponentFactory::ComponentFactory() {
        registerComponents();
    }

    void ComponentFactory::registerComponents() {
        _creators["input"] = [this](const std::string &name) { return createInput(name); };
        _creators["output"] = [this](const std::string &name) { return createOutput(name); };
        _creators["true"] = [this](const std::string &name) { return createTrue(name); };
        _creators["false"] = [this](const std::string &name) { return createFalse(name); };
        _creators["clock"] = [this](const std::string &name) { return createClock(name); };
        _creators["and"] = [this](const std::string &name) { return createAnd(name); };
        _creators["or"] = [this](const std::string &name) { return createOr(name); };
        _creators["xor"] = [this](const std::string &name) { return createXor(name); };
        _creators["not"] = [this](const std::string &name) { return createNot(name); };
        _creators["4081"] = [this](const std::string &name) { return create4081(name); };
        _creators["4071"] = [this](const std::string &name) { return create4071(name); };
    }

    std::unique_ptr<IComponent> ComponentFactory::createComponent(const std::string &type, const std::string &name) {
        auto it = _creators.find(type);
        if (it == _creators.end()) {
            throw std::invalid_argument("Unknown component type: " + type);
        }
        return it->second(name);
    }

    std::unique_ptr<IComponent> ComponentFactory::createInput(const std::string &name) const {
        return std::make_unique<InputComponent>(name);
    }

    std::unique_ptr<IComponent> ComponentFactory::createOutput(const std::string &name) const {
        return std::make_unique<OutputComponent>(name);
    }

    std::unique_ptr<IComponent> ComponentFactory::createTrue(const std::string &name) const {
        return std::make_unique<TrueComponent>(name);
    }

    std::unique_ptr<IComponent> ComponentFactory::createFalse(const std::string &name) const {
        return std::make_unique<FalseComponent>(name);
    }

    std::unique_ptr<IComponent> ComponentFactory::createClock(const std::string &name) const {
        return std::make_unique<ClockComponent>(name);
    }

    std::unique_ptr<IComponent> ComponentFactory::createAnd(const std::string &name) const {
        return std::make_unique<AndGate>(name);
    }

    std::unique_ptr<IComponent> ComponentFactory::createOr(const std::string &name) const {
        return std::make_unique<OrGate>(name);
    }

    std::unique_ptr<IComponent> ComponentFactory::createXor(const std::string &name) const {
        return std::make_unique<XorGate>(name);
    }

    std::unique_ptr<IComponent> ComponentFactory::createNot(const std::string &name) const {
        return std::make_unique<NotGate>(name);
    }

    std::unique_ptr<IComponent> ComponentFactory::create4081(const std::string &name) const {
        return std::make_unique<Chip4081>(name);
    }

    std::unique_ptr<IComponent> ComponentFactory::create4071(const std::string &name) const {
        return std::make_unique<Chip4071>(name);
    }
}
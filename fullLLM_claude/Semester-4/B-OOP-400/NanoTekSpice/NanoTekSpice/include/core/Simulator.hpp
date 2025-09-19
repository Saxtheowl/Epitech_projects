/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Circuit simulator
*/

#pragma once

#include "nts/IComponent.hpp"
#include "core/Parser.hpp"
#include "components/basic/Input.hpp"
#include "components/basic/Output.hpp"
#include "components/basic/Clock.hpp"
#include <string>
#include <map>
#include <memory>

namespace nts {
    class Simulator {
    private:
        Parser _parser;
        std::size_t _currentTick = 0;

    public:
        Simulator();
        ~Simulator() = default;

        void loadCircuit(const std::string &filename);
        void simulate();
        void display();
        void setInputValue(const std::string &name, nts::Tristate value);
        void loop();
        void run();

    private:
        std::string tristateToString(nts::Tristate value);
        nts::Tristate stringToTristate(const std::string &str);
        void processCommand(const std::string &command);
        bool isInput(const std::string &name);
        bool isOutput(const std::string &name);
        bool isClock(const std::string &name);
    };
}
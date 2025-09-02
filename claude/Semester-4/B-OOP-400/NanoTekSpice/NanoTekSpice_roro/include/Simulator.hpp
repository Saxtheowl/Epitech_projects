/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Main simulator class
*/

#ifndef SIMULATOR_HPP_
#define SIMULATOR_HPP_

#include "Parser.hpp"
#include "IComponent.hpp"
#include "Components.hpp"
#include <memory>
#include <map>
#include <string>

namespace nts {
    class Simulator {
    private:
        std::map<std::string, std::unique_ptr<IComponent>> _components;
        std::size_t _currentTick;
        bool _running;

    public:
        Simulator();
        ~Simulator() = default;

        void loadCircuit(const std::string &filename);
        void run();
        void runInteractive();

    private:
        void processCommand(const std::string &command);
        void simulate();
        void display();
        void setInputValue(const std::string &inputName, Tristate value);
        void loop();
        void exitSimulation();
        
        Tristate parseTristate(const std::string &value);
        std::string tristateToString(Tristate value);
        
        void showInputs();
        void showOutputs();
        
        bool isInput(const std::string &componentName);
        bool isOutput(const std::string &componentName);
        bool isClock(const std::string &componentName);
    };
}

#endif /* !SIMULATOR_HPP_ */
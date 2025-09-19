/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Circuit simulator implementation
*/

#include "core/Simulator.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <csignal>

namespace nts {
    static bool loopRunning = false;

    void signalHandler(int signal) {
        if (signal == SIGINT) {
            loopRunning = false;
        }
    }

    Simulator::Simulator() {}

    void Simulator::loadCircuit(const std::string &filename) {
        try {
            _parser.parseFile(filename);
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            exit(84);
        }
    }

    void Simulator::simulate() {
        _currentTick++;
        for (auto &component : _parser.getComponents()) {
            component.second->simulate(_currentTick);
        }
    }

    void Simulator::display() {
        std::cout << "tick: " << _currentTick << std::endl;

        // Display inputs
        std::cout << "input(s):" << std::endl;
        std::vector<std::string> inputNames;
        for (const auto &component : _parser.getComponents()) {
            if (isInput(component.first) || isClock(component.first)) {
                inputNames.push_back(component.first);
            }
        }
        std::sort(inputNames.begin(), inputNames.end());
        for (const auto &name : inputNames) {
            nts::Tristate value = _parser.getComponents()[name]->compute(1);
            std::cout << name << ": " << tristateToString(value) << std::endl;
        }

        // Display outputs
        std::cout << "output(s):" << std::endl;
        std::vector<std::string> outputNames;
        for (const auto &component : _parser.getComponents()) {
            if (isOutput(component.first)) {
                outputNames.push_back(component.first);
            }
        }
        std::sort(outputNames.begin(), outputNames.end());
        for (const auto &name : outputNames) {
            nts::Tristate value = _parser.getComponents()[name]->compute(1);
            std::cout << name << ": " << tristateToString(value) << std::endl;
        }
    }

    void Simulator::setInputValue(const std::string &name, nts::Tristate value) {
        auto it = _parser.getComponents().find(name);
        if (it == _parser.getComponents().end()) {
            std::cerr << "Unknown component: " << name << std::endl;
            return;
        }

        if (isInput(name)) {
            Input *input = dynamic_cast<Input*>(it->second.get());
            if (input) {
                input->setState(value);
            }
        } else if (isClock(name)) {
            Clock *clock = dynamic_cast<Clock*>(it->second.get());
            if (clock) {
                clock->setState(value);
            }
        } else {
            std::cerr << "Component " << name << " is not an input or clock" << std::endl;
        }
    }

    void Simulator::loop() {
        signal(SIGINT, signalHandler);
        loopRunning = true;

        while (loopRunning) {
            simulate();
            display();
        }
    }

    void Simulator::run() {
        std::string line;

        while (true) {
            std::cout << "> ";
            if (!std::getline(std::cin, line)) {
                // EOF reached (Ctrl+D)
                break;
            }

            if (line.empty()) {
                continue;
            }

            processCommand(line);
        }
    }

    void Simulator::processCommand(const std::string &command) {
        if (command == "exit") {
            exit(0);
        } else if (command == "display") {
            display();
        } else if (command == "simulate") {
            simulate();
        } else if (command == "loop") {
            loop();
        } else if (command.find('=') != std::string::npos) {
            // Input assignment
            size_t pos = command.find('=');
            std::string name = command.substr(0, pos);
            std::string value = command.substr(pos + 1);

            // Trim whitespace
            name.erase(std::remove_if(name.begin(), name.end(), ::isspace), name.end());
            value.erase(std::remove_if(value.begin(), value.end(), ::isspace), value.end());

            nts::Tristate tristate = stringToTristate(value);
            setInputValue(name, tristate);
        } else {
            std::cerr << "Unknown command: " << command << std::endl;
        }
    }

    std::string Simulator::tristateToString(nts::Tristate value) {
        switch (value) {
            case nts::Tristate::True:
                return "1";
            case nts::Tristate::False:
                return "0";
            case nts::Tristate::Undefined:
                return "U";
            default:
                return "U";
        }
    }

    nts::Tristate Simulator::stringToTristate(const std::string &str) {
        if (str == "1") {
            return nts::Tristate::True;
        } else if (str == "0") {
            return nts::Tristate::False;
        } else if (str == "U") {
            return nts::Tristate::Undefined;
        }
        return nts::Tristate::Undefined;
    }

    bool Simulator::isInput(const std::string &name) {
        auto it = _parser.getComponents().find(name);
        if (it != _parser.getComponents().end()) {
            return dynamic_cast<Input*>(it->second.get()) != nullptr;
        }
        return false;
    }

    bool Simulator::isOutput(const std::string &name) {
        auto it = _parser.getComponents().find(name);
        if (it != _parser.getComponents().end()) {
            return dynamic_cast<Output*>(it->second.get()) != nullptr;
        }
        return false;
    }

    bool Simulator::isClock(const std::string &name) {
        auto it = _parser.getComponents().find(name);
        if (it != _parser.getComponents().end()) {
            return dynamic_cast<Clock*>(it->second.get()) != nullptr;
        }
        return false;
    }
}
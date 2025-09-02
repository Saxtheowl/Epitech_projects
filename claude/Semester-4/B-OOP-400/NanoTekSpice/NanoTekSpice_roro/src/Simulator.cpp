/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Main simulator implementation
*/

#include "Simulator.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <csignal>
#include <unistd.h>

namespace nts {
    static bool g_interrupted = false;
    
    static void signalHandler(int signal) {
        if (signal == SIGINT) {
            g_interrupted = true;
            std::cout << std::endl;
        }
    }

    Simulator::Simulator() : _currentTick(0), _running(false) {
        std::signal(SIGINT, signalHandler);
    }

    void Simulator::loadCircuit(const std::string &filename) {
        Parser parser;
        parser.parseFile(filename);
        _components = std::move(parser.getComponents());
    }

    void Simulator::run() {
        runInteractive();
    }

    void Simulator::runInteractive() {
        _running = true;
        std::string line;
        
        while (_running && std::getline(std::cin, line)) {
            try {
                processCommand(line);
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
            
            if (_running) {
                std::cout << "> ";
            }
        }
    }

    void Simulator::processCommand(const std::string &command) {
        std::istringstream iss(command);
        std::string cmd;
        iss >> cmd;
        
        if (cmd.empty()) {
            return;
        }
        
        if (cmd == "exit") {
            exitSimulation();
        } else if (cmd == "simulate") {
            simulate();
        } else if (cmd == "display") {
            display();
        } else if (cmd == "loop") {
            loop();
        } else if (cmd.find('=') != std::string::npos) {
            // Handle input=value
            auto pos = cmd.find('=');
            std::string inputName = cmd.substr(0, pos);
            std::string valueStr = cmd.substr(pos + 1);
            
            Tristate value = parseTristate(valueStr);
            setInputValue(inputName, value);
        } else {
            throw std::invalid_argument("Unknown command: " + cmd);
        }
    }

    void Simulator::simulate() {
        _currentTick++;
        
        // Simulate all components
        for (auto &pair : _components) {
            pair.second->simulate(_currentTick);
        }
    }

    void Simulator::display() {
        std::cout << "tick: " << _currentTick << std::endl;
        
        showInputs();
        showOutputs();
    }

    void Simulator::showInputs() {
        std::cout << "input(s):" << std::endl;
        
        std::vector<std::string> inputNames;
        for (const auto &pair : _components) {
            if (isInput(pair.first) || isClock(pair.first)) {
                inputNames.push_back(pair.first);
            }
        }
        
        std::sort(inputNames.begin(), inputNames.end());
        
        for (const std::string &name : inputNames) {
            Tristate value = _components[name]->compute(1);
            std::cout << name << ": " << tristateToString(value) << std::endl;
        }
    }

    void Simulator::showOutputs() {
        std::cout << "output(s):" << std::endl;
        
        std::vector<std::string> outputNames;
        for (const auto &pair : _components) {
            if (isOutput(pair.first)) {
                outputNames.push_back(pair.first);
            }
        }
        
        std::sort(outputNames.begin(), outputNames.end());
        
        for (const std::string &name : outputNames) {
            Tristate value = _components[name]->compute(1);
            std::cout << name << ": " << tristateToString(value) << std::endl;
        }
    }

    void Simulator::setInputValue(const std::string &inputName, Tristate value) {
        auto it = _components.find(inputName);
        if (it == _components.end()) {
            throw std::invalid_argument("Component not found: " + inputName);
        }
        
        if (isInput(inputName)) {
            auto *inputComp = dynamic_cast<InputComponent*>(it->second.get());
            if (inputComp) {
                inputComp->setValue(value);
            }
        } else if (isClock(inputName)) {
            auto *clockComp = dynamic_cast<ClockComponent*>(it->second.get());
            if (clockComp) {
                clockComp->setValue(value);
            }
        } else {
            throw std::invalid_argument("Component is not an input: " + inputName);
        }
    }

    void Simulator::loop() {
        g_interrupted = false;
        
        while (!g_interrupted) {
            simulate();
            display();
            
            // Small delay to avoid too fast execution
            usleep(100000); // 0.1 second
        }
        
        g_interrupted = false;
    }

    void Simulator::exitSimulation() {
        _running = false;
    }

    Tristate Simulator::parseTristate(const std::string &value) {
        if (value == "0") return False;
        if (value == "1") return True;
        if (value == "U") return Undefined;
        throw std::invalid_argument("Invalid tristate value: " + value);
    }

    std::string Simulator::tristateToString(Tristate value) {
        switch (value) {
            case True: return "1";
            case False: return "0";
            case Undefined: return "U";
            default: return "U";
        }
    }

    bool Simulator::isInput(const std::string &componentName) {
        auto it = _components.find(componentName);
        if (it == _components.end()) return false;
        return dynamic_cast<InputComponent*>(it->second.get()) != nullptr;
    }

    bool Simulator::isOutput(const std::string &componentName) {
        auto it = _components.find(componentName);
        if (it == _components.end()) return false;
        return dynamic_cast<OutputComponent*>(it->second.get()) != nullptr;
    }

    bool Simulator::isClock(const std::string &componentName) {
        auto it = _components.find(componentName);
        if (it == _components.end()) return false;
        return dynamic_cast<ClockComponent*>(it->second.get()) != nullptr;
    }
}
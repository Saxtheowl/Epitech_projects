/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Main entry point for NanoTekSpice
*/

#include "Simulator.hpp"
#include <iostream>

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <circuit.nts>" << std::endl;
        return 84;
    }

    try {
        nts::Simulator simulator;
        simulator.loadCircuit(argv[1]);
        simulator.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    return 0;
}
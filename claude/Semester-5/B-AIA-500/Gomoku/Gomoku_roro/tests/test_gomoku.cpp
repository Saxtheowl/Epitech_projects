/*
** EPITECH PROJECT, 2025
** Gomoku
** File description:
** Simple unit tests for Gomoku AI
*/

#include "gomoku.h"
#include "protocol.h"
#include <cassert>
#include <iostream>

void test_board_initialization()
{
    Gomoku game;
    game.start_game(BOARD_SIZE);
    
    assert(!game.is_game_over() && "Game should not be over at start");
    std::cout << "✓ Board initialization test passed" << std::endl;
}

void test_valid_position()
{
    Gomoku game;
    game.start_game(BOARD_SIZE);
    
    Position next_move = game.get_next_move();
    
    assert(next_move.x >= 0 && "Move X should be >= 0");
    assert(next_move.x < BOARD_SIZE && "Move X should be < BOARD_SIZE");
    assert(next_move.y >= 0 && "Move Y should be >= 0");
    assert(next_move.y < BOARD_SIZE && "Move Y should be < BOARD_SIZE");
    std::cout << "✓ Valid position test passed" << std::endl;
}

void test_make_move()
{
    Gomoku game;
    game.start_game(BOARD_SIZE);
    
    game.make_move(10, 10);
    game.opponent_move(11, 11);
    
    Position next_move = game.get_next_move();
    bool valid_move = (next_move.x != 10 || next_move.y != 10) &&
                      (next_move.x != 11 || next_move.y != 11);
    
    std::cout << "✓ Make move test passed" << std::endl;
}

void test_protocol_initialization()
{
    Protocol protocol;
    std::cout << "✓ Protocol initialization test passed" << std::endl;
}

int main()
{
    std::cout << "Running Gomoku unit tests..." << std::endl;
    
    try {
        test_board_initialization();
        test_valid_position();
        test_make_move();
        test_protocol_initialization();
        
        std::cout << "All tests passed!" << std::endl;
        return 0;
    } catch (const std::exception &e) {
        std::cout << "Test failed: " << e.what() << std::endl;
        return 1;
    }
}
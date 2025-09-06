/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** ECS system tests
*/

#include "ECS.hpp"
#include "Components.hpp"
#include <cassert>
#include <iostream>

void test_entity_creation()
{
    ECS::Registry registry;
    
    auto entity1 = registry.createEntity();
    auto entity2 = registry.createEntity();
    
    assert(entity1 != entity2);
    std::cout << "✓ Entity creation test passed" << std::endl;
}

void test_component_management()
{
    ECS::Registry registry;
    
    auto entity = registry.createEntity();
    
    Components::Position pos(100.0f, 200.0f);
    registry.addComponent(entity, pos);
    
    auto* retrievedPos = registry.getComponent<Components::Position>(entity);
    assert(retrievedPos != nullptr);
    assert(retrievedPos->x == 100.0f);
    assert(retrievedPos->y == 200.0f);
    
    std::cout << "✓ Component management test passed" << std::endl;
}

void test_component_query()
{
    ECS::Registry registry;
    
    auto entity1 = registry.createEntity();
    auto entity2 = registry.createEntity();
    auto entity3 = registry.createEntity();
    
    registry.addComponent(entity1, Components::Position(0, 0));
    registry.addComponent(entity1, Components::Velocity(0, 0));
    
    registry.addComponent(entity2, Components::Position(0, 0));
    
    registry.addComponent(entity3, Components::Velocity(0, 0));
    
    auto entities = registry.getEntitiesWith({
        std::type_index(typeid(Components::Position)),
        std::type_index(typeid(Components::Velocity))
    });
    
    assert(entities.size() == 1);
    assert(entities[0] == entity1);
    
    std::cout << "✓ Component query test passed" << std::endl;
}

int main()
{
    std::cout << "Running ECS tests..." << std::endl;
    
    try {
        test_entity_creation();
        test_component_management();
        test_component_query();
        
        std::cout << "All ECS tests passed!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }
}
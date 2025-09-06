/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Entity Component System header
*/

#pragma once

#include <unordered_map>
#include <vector>
#include <memory>
#include <typeindex>
#include <functional>

namespace ECS {
    using Entity = std::size_t;
    using ComponentType = std::size_t;

    class IComponent {
    public:
        virtual ~IComponent() = default;
    };

    template<typename T>
    class Component : public IComponent {
    public:
        T data;
        
        Component(const T& d) : data(d) {}
    };

    class Registry {
    private:
        std::unordered_map<Entity, std::unordered_map<std::type_index, std::unique_ptr<IComponent>>> entities_;
        Entity next_entity_id_;
        
    public:
        Registry() : next_entity_id_(0) {}
        
        Entity createEntity() {
            return next_entity_id_++;
        }
        
        void destroyEntity(Entity entity) {
            entities_.erase(entity);
        }
        
        template<typename T>
        void addComponent(Entity entity, const T& component) {
            entities_[entity][std::type_index(typeid(T))] = 
                std::make_unique<Component<T>>(component);
        }
        
        template<typename T>
        T* getComponent(Entity entity) {
            auto entity_it = entities_.find(entity);
            if (entity_it == entities_.end()) {
                return nullptr;
            }
            
            auto comp_it = entity_it->second.find(std::type_index(typeid(T)));
            if (comp_it == entity_it->second.end()) {
                return nullptr;
            }
            
            return &static_cast<Component<T>*>(comp_it->second.get())->data;
        }
        
        template<typename T>
        bool hasComponent(Entity entity) {
            return getComponent<T>(entity) != nullptr;
        }
        
        template<typename T>
        void removeComponent(Entity entity) {
            auto entity_it = entities_.find(entity);
            if (entity_it != entities_.end()) {
                entity_it->second.erase(std::type_index(typeid(T)));
            }
        }
        
        std::vector<Entity> getEntitiesWith(std::vector<std::type_index> types) {
            std::vector<Entity> result;
            
            for (const auto& [entity, components] : entities_) {
                bool hasAll = true;
                for (const auto& type : types) {
                    if (components.find(type) == components.end()) {
                        hasAll = false;
                        break;
                    }
                }
                if (hasAll) {
                    result.push_back(entity);
                }
            }
            
            return result;
        }
    };

    class ISystem {
    public:
        virtual ~ISystem() = default;
        virtual void update(Registry& registry, float deltaTime) = 0;
    };
}
#pragma once
#include "common/Base.h"
#include "ecs/Components.h"

namespace VM
{
    struct EntitySnapshot
    {
        entt::entity entity;
        entt::entity parent = entt::null;
        std::unordered_map<std::type_index, std::any> components;
        std::vector<EntitySnapshot> children;
    };
    
} // namespace VM

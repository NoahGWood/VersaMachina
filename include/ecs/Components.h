#pragma once
#include "common/Base.h"
#include "block/BlockSpec.h"
#include <imgui.h>

namespace VM
{
    struct Schema{
        int version = 1;
    };
    struct TagComponent{
        std::string name;

        TagComponent() = default;
        TagComponent(const std::string& n) : name(n) {}
    };
    struct HierarchyComponent{
        entt::entity parent{ entt::null };
        std::vector<entt::entity> children;

        HierarchyComponent() = default;
        HierarchyComponent(const entt::entity p) : parent(p) {}
        HierarchyComponent(const entt::entity p, std::vector<entt::entity> c)
            : parent(p), children(c) {}
        
    };
    struct TransformComponent{
        glm::vec2 pos;
    };

    struct BlockInstance{
        std::string instanceId;
        std::string blockId;
        std::string label;
        ImVec2 position;
        bool selected{false};
        // std::vector<PortSpec> ports;
        std::vector<std::string> ports;
        // index = local port index, value = other entity port index
        std::unordered_map<size_t, std::vector<std::pair<entt::entity, size_t>>> connections;
    };

    struct CWire{
        entt::entity fromBlock;
        entt::entity toBlock;
        std::string fromPortId;
        std::string toPortId;
    };
} // namespace VM

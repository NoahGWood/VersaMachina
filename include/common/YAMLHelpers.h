#pragma once
#include <yaml-cpp/yaml.h>
#include <imgui.h>

namespace YAML
{
    template<>
    struct convert<ImVec2>
    {
        static Node encode(const ImVec2& rhs){
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }
        static bool decode(const Node& node, ImVec2& rhs) {
            if (!node.IsSequence() || node.size() != 2)
                return false;
            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            return true;
        }
    };
    
} // namespace YAML

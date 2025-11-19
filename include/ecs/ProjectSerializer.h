#pragma once
#include "common/Base.h"
#include <ecs/Project.h>
#include <common/YAMLHelpers.h>
namespace VM
{
    static void SerializeComponent(YAML::Emitter& out, std::string name,
        std::unordered_map<std::string, std::string> kv);
    static void SerializeEntity(YAML::Emitter& out, entt::entity entity, Project& project);

    class ProjectSerializer{
        public:
            ProjectSerializer(Project& proj) : m_Project(proj) {
            }

            void Serialize(std::filesystem::path path);

            void Deserialize(const std::filesystem::path& path);
        private:
            Project& m_Project;
    };
} // namespace VM

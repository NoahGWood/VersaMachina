#include "ecs/ProjectSerializer.h"
#include "ecs/Components.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

namespace VM
{

    YAML::Emitter &operator<<(YAML::Emitter &out, const glm::vec4 &v)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
        return out;
    }
    YAML::Emitter &operator<<(YAML::Emitter &out, const glm::vec3 &v)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
        return out;
    }
    YAML::Emitter &operator<<(YAML::Emitter &out, const glm::vec2 &v)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
        return out;
    }
    YAML::Emitter &operator<<(YAML::Emitter& out, const ImVec2& v){
        out << YAML::Flow;
        out << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
        return out;
    }
    YAML::Emitter &operator<<(YAML::Emitter &out, const glm::mat4 &v)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << v[0][0] << v[0][1] << v[0][2] << v[0][3] << v[1][0] << v[1][1] << v[1][2] << v[1][3] << v[2][0] << v[2][1] << v[2][2] << v[2][3] << v[3][0] << v[3][1] << v[3][2] << v[3][3] << YAML::EndSeq;
        return out;
    }
    YAML::Emitter &operator<<(YAML::Emitter &out, const glm::mat3 &v)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << v[0][0] << v[0][1] << v[0][2] << v[1][0] << v[1][1] << v[1][2] << v[2][0] << v[2][1] << v[2][2] << YAML::EndSeq;
        return out;
    }
    YAML::Emitter& operator<<(YAML::Emitter& out, const std::vector<std::string>& v) {
        out << YAML::Flow;
        out << YAML::BeginSeq;
        for (auto& e : v) {
            out << e;
        }
        out << YAML::EndSeq;
        return out;
    }
    YAML::Emitter &operator<<(YAML::Emitter &out, const entt::entity& v){
        out << std::to_string((uint32_t)entt::to_integral(v));
        return out;
    }
    // connections[i] is a vector of {entity, port}
    YAML::Emitter& operator<<(YAML::Emitter &out,
        const std::unordered_map<size_t,
        std::vector<std::pair<entt::entity, size_t>>>& v)
    {
        out << YAML::BeginMap;
        for (auto& [index, cons] : v) {
            out << YAML::Key << index;
            out << YAML::Value << YAML::BeginSeq;
            for (auto& [e, p] : cons) {
                out << YAML::BeginMap;
                out << YAML::Key << "Entity" << YAML::Value << (uint32_t)entt::to_integral(e);
                out << YAML::Key << "Port"   << YAML::Value << p;
                out << YAML::EndMap;
            }
            out << YAML::EndSeq;
        }
        out << YAML::EndMap;
        return out;
    }
    YAML::Emitter &operator<<(YAML::Emitter &out, const size_t& v){
        out << std::to_string(v);
        return out;
    }
    // YAML::Emitter &operator<<(YAML::Emitter& out, const PortSpec &v){
    //     out << YAML::Key << "PortSpec";
    //     out << YAML::BeginMap;
    //         out << YAML::Key << "ID" << YAML::Value << v.id;
    //         out << YAML::Key << "Name" << YAML::Value << v.name;
    //         out << YAML::Key << "Kind" << YAML::Value << v.kind;
    //         out << YAML::Key << "Direction" << YAML::Value << v.direction;
    //         out << YAML::Key << "Tags";
    //         out << YAML::BeginMap;
    //             for(auto& [k,v] : v.tags){
    //                 out << YAML::Key << k << YAML::Value << v;
    //             }
    //         out << YAML::EndMap;
    //     out << YAML::EndMap;
    // }

    static void SerializeComponent(YAML::Emitter &out, std::string name, std::unordered_map<std::string, std::string> kv)
    {
        out << YAML::Key << name;
        out << YAML::BeginMap;
        for (auto [key, value] : kv)
        {
            out << YAML::Key << key << YAML::Value << value;
        }
        out << YAML::EndMap;
    }

    static void SerializeEntity(YAML::Emitter &out, entt::entity entity, Project &project)
    {
        out << YAML::BeginMap;
        out << YAML::Key << "Entity" << YAML::Value << (uint32_t)entt::to_integral(entity);
        // out << YAML::Key << "Components" << YAML::Value << YAML::BeginMap;
        if (project.HasComponent<TagComponent>(entity))
        {
            auto tc = project.GetComponent<TagComponent>(entity).name;
            SerializeComponent(out, "TagComponent", {{"Tag", tc}});
        }
        if (project.HasComponent<TransformComponent>(entity))
        {
            auto tc = project.GetComponent<TransformComponent>(entity);
            out << YAML::Key << "TransformComponent";
            out << YAML::BeginMap << "Position" << tc.pos << YAML::EndMap;
        }
        if (project.HasComponent<HierarchyComponent>(entity))
        {
            auto hc = project.GetComponent<HierarchyComponent>(entity);
            std::unordered_map<std::string, std::string> cmd;
            cmd["Parent"] = "NULL";
            if (hc.parent != entt::null)
                cmd["Parent"] = std::to_string((uint32_t)entt::to_integral(hc.parent));
            SerializeComponent(out, "HierarchyComponent", cmd);
        }
        if(project.HasComponent<BlockInstance>(entity)){
            auto& bi = project.GetComponent<BlockInstance>(entity);
            out << YAML::Key << "BlockInstance";
            out << YAML::BeginMap;
                out << YAML::Key << "Label" << YAML::Value << bi.label;
                out << YAML::Key << "Selected" << YAML::Value << bi.selected;
                out << YAML::Key << "Position" << YAML::Value << bi.position;
                out << YAML::Key << "Ports" << bi.ports;
                out << YAML::Key << "Connections" << bi.connections;
            out << YAML::EndMap;
        }
        out << YAML::EndMap; // Entity
    }

    void ProjectSerializer::Serialize(std::filesystem::path path)
    {
        path.replace_extension("vproj");
        std::ofstream ofs(path);
        if (!ofs.is_open())
        {
            CORE_ERROR("Failed to open project file: {}", path.string());
            return;
        }
        YAML::Emitter out;
        out << YAML::BeginMap;
        out << YAML::Key << "Project" << YAML::Value << m_Project.GetName(); // Todo later on
        out << YAML::Key << "Version" << YAML::Value << 1;
        out << YAML::Key << "Entities" << YAML::Value;
        auto &reg = m_Project.GetRegistry();
        out << YAML::BeginSeq;
        for (auto e : reg.view<entt::entity>())
        {
            SerializeEntity(out, e, m_Project);
        }
        out << YAML::EndSeq;
        ofs << out.c_str();
    }

    void ProjectSerializer::Deserialize(const std::filesystem::path &path)
    {
        m_Project.Clear();
        try
        {
            YAML::Node data = YAML::LoadFile(path);
            if (!data["Project"])
            {
                CORE_ERROR("Not a valid project file!");
                return;
            }
            std::string projName = data["Project"].as<std::string>();
            CORE_TRACE("Deserializing project {0}", projName);
            m_Project.SetName(projName);

            auto entities = data["Entities"];
            if (entities)
            {
                for (auto entity : entities)
                {
                    // Read and build all entities first
                    uint32_t uuid = entity["Entity"].as<uint32_t>();
                    entt::entity id{uuid};
                    std::string name;
                    if (entity["TagComponent"])
                    {
                        name = entity["TagComponent"]["Tag"].as<std::string>();
                        CORE_INFO("NAME: {0}", name);
                    }
                    else
                    {
                        CORE_INFO("NO NAME FOUND");
                    }
                    entt::entity e = m_Project.CreateEntity(id, name);
                }
                for (auto entity : entities)
                {
                    uint32_t uuid = entity["Entity"].as<uint32_t>();
                    entt::entity id{uuid};
                    if(entity["BlockInstance"]){
                        auto& b = m_Project.AddComponent<BlockInstance>(id);
                        b.label = entity["BlockInstance"]["Label"].as<std::string>();
                        b.selected = entity["BlockInstance"]["Selected"].as<bool>();
                        b.position = entity["BlockInstance"]["Position"].as<ImVec2>();
                        b.ports = entity["BlockInstance"]["Ports"].as<std::vector<std::string>>();
                        auto conNode = entity["BlockInstance"]["Connections"];
                        if (conNode) {
                            for (auto it = conNode.begin(); it != conNode.end(); ++it) {

                                size_t portIndex = it->first.as<size_t>();
                                YAML::Node list = it->second;

                                for (auto item : list) {
                                    entt::entity other =
                                        (entt::entity)item["Entity"].as<uint32_t>();

                                    size_t otherPort =
                                        item["Port"].as<size_t>();

                                    b.connections[portIndex].push_back({ other, otherPort });
                                }
                            }
                        }
                    }
                    if (entity["HierarchyComponent"])
                    {
                        std::string parent = entity["HierarchyComponent"]["Parent"].as<std::string>();
                        auto &h = m_Project.GetComponent<HierarchyComponent>(id);
                        if (parent != "NULL")
                        {
                            CORE_INFO("SETTING PARENT: {0}", parent);
                            int pid = std::stoul(parent, nullptr, 10);
                            m_Project.SetParent(id, (entt::entity)pid);
                        }
                    }
                }
            }
        }
        catch (const YAML::ParserException e)
        {
            CORE_ERROR("Error parsing file: {0}", e.what());
            return;
        }
        catch (const YAML::BadSubscript e)
        {
            CORE_ERROR("Error parsing file: {0}", e.what());
            return;
        }
    }

} // namespace VM

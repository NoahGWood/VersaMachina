#include "pch.h"
#include "Core/GLM_Conversion.h"
#include "ECS/SceneSerializer.h"
#include "ECS/Entity.h"
#include "ECS/Components.h"
#include "Camera/CameraSettings.h"
#include <fstream>
#include <yaml-cpp/yaml.h>
#include <glm/gtx/string_cast.hpp>

namespace VersaMachina
{
    namespace ECS
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

        static void SerializeComponent(YAML::Emitter &out, std::string name, std::unordered_map<std::string, std::string> kv)
        {
            out << YAML::Key << name; // Set component name

            out << YAML::BeginMap; // Component
            for (auto [key, value] : kv)
            {
                out << YAML::Key << key << YAML::Value << value;
            }

            out << YAML::EndMap; // Component
        }

        static void SerializeEntity(YAML::Emitter &out, Entity entity)
        {
            out << YAML::BeginMap; // Entity

            out << YAML::Key << "Entity" << YAML::Value << "1234"; // EntityID

            if (entity.HasComponent<TagComponent>())
            {
                auto &tag = entity.GetComponent<TagComponent>().Tag;
                SerializeComponent(out, "TagComponent", {{"Tag", tag}});
            }
            if (entity.HasComponent<TransformComponent>())
            {
                auto &tc = entity.GetComponent<TransformComponent>();
                out << YAML::Key << "TransformComponent"; // Set component name

                out << YAML::BeginMap; // Component
                out << YAML::Key << "Transform" << YAML::Value << tc.Transform;
                out << YAML::Key << "Translation" << YAML::Value << tc.Translation;
                out << YAML::Key << "Rotation" << YAML::Value << tc.Rotation;
                out << YAML::Key << "Scale" << YAML::Value << tc.Scale;
                out << YAML::EndMap; // Component
            }
            if (entity.HasComponent<SpriteRendererComponent>())
            {
                auto &sr = entity.GetComponent<SpriteRendererComponent>();
                // TODO: Add support for textures
                out << YAML::Key << "SpriteRendererComponent"; // Set component name
                out << YAML::BeginMap;                         // Component
                out << YAML::Key << "Color" << YAML::Value << sr.Color;
                out << YAML::EndMap; // Component
            }
            if (entity.HasComponent<CameraComponent>())
            {
                auto &cam = entity.GetComponent<CameraComponent>();
                Ref<Camera::CameraSettings> settings = cam.m_Camera->GetSettings();

                out << YAML::Key << "CameraComponent";
                out << YAML::BeginMap; // CameraComponent
                out << YAML::Key << "Camera" << YAML::Value;
                out << YAML::BeginMap; // Camera
                out << YAML::Key << "CameraType" << YAML::Value << (int)settings->Type;
                out << YAML::Key << "Viewport" << YAML::Value << settings->Viewport;
                out << YAML::Key << "FieldOfView" << YAML::Value << settings->FieldOfView;
                out << YAML::Key << "FieldOfViewAxis" << YAML::Value << settings->FieldOfViewAxis;
                out << YAML::Key << "AspectRatio" << YAML::Value << settings->AspectRatio;
                out << YAML::Key << "FixedAspectRatio" << YAML::Value << settings->FixedAspectRatio;
                out << YAML::Key << "NearClip" << YAML::Value << settings->NearClip;
                out << YAML::Key << "FarClip" << YAML::Value << settings->FarClip;
                out << YAML::Key << "Transform" << YAML::Value << settings->Transform;
                out << YAML::Key << "ZoomLevel" << YAML::Value << settings->ZoomLevel;
                out << YAML::Key << "MoveSpeed" << YAML::Value << settings->MoveSpeed;
                out << YAML::Key << "RotateSpeed" << YAML::Value << settings->RotateSpeed;
                out << YAML::EndMap; // Camera
                out << YAML::Key << "Primary" << YAML::Value << cam.Primary;

                out << YAML::EndMap; // CameraComponent
            }

            out << YAML::EndMap; // Entity
        }

        SceneSerializer::SceneSerializer(const Ref<Scene> &scene)
            : m_Scene(scene) {}

        void SceneSerializer::Serialize(const std::string &filepath)
        {
            YAML::Emitter out;
            out << YAML::BeginMap;
            out << YAML::Key << "Scene" << YAML::Value << "Untitled";
            out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
            m_Scene->m_Registry.each([&](auto entityID)
                                     {
                Entity entity = { entityID, m_Scene.get() };
                if(!entity)
                    return;
                SerializeEntity(out, entity); });
            out << YAML::EndSeq;
            out << YAML::EndMap;

            std::ofstream fout(filepath);
            fout << out.c_str();
        }
        void SceneSerializer::SerializeRuntime(const std::string &filepath)
        {
            VM_CORE_ASSERT(false, "Runtime Scene Serialization Not Implemented.");
        }
        bool SceneSerializer::Deserialize(const std::string &filepath)
        {
            YAML::Node data = YAML::LoadFile(filepath);
            if (!data["Scene"])
                return false;

            std::string sceneName = data["Scene"].as<std::string>();
            VM_CORE_TRACE("Deserializing scene {0}", sceneName);

            auto entities = data["Entities"];
            if (entities)
            {
                for (auto entity : entities)
                {
                    VM_CORE_TRACE("Entity");
                    uint64_t uuid = entity["Entity"].as<uint64_t>();
                    std::string name;
                    if (entity["TagComponent"])
                        name = entity["TagComponent"]["Tag"].as<std::string>();

                    VM_CORE_TRACE("Deserialized entity with ID = {0}, name = {1}", uuid, name);

                    Entity e = m_Scene->CreateEntity(name);

                    auto transformComponent = entity["TransformComponent"];
                    if (transformComponent)
                    {
                        VM_CORE_TRACE("Found Transform Component");

                        auto &tc = e.GetComponent<TransformComponent>();
                        tc.Transform = transformComponent["Transform"].as<glm::mat4>();
                        tc.Translation = transformComponent["Translation"].as<glm::vec3>();
                        tc.Rotation = transformComponent["Rotation"].as<glm::vec3>();
                        tc.Scale = transformComponent["Scale"].as<glm::vec3>();
                    }

                    auto spriteComponent = entity["SpriteRendererComponent"];
                    if (spriteComponent)
                    {
                        VM_CORE_TRACE("Found Sprite Component");
                        auto &sc = e.AddComponent<SpriteRendererComponent>();
                        sc.Color = spriteComponent["Color"].as<glm::vec4>();
                    }
                    auto cameraComponent = entity["CameraComponent"];
                    if (cameraComponent)
                    {
                        VM_CORE_TRACE("Found Camera Component");

                        auto &cc = e.AddComponent<CameraComponent>();
                        cc.Primary = cameraComponent["Primary"].as<bool>();
                        auto cam = cameraComponent["Camera"];
                        cc.m_Camera->SetType(cam["CameraType"].as<int>());
                        cc.m_Camera->SetViewport(cam["Viewport"].as<glm::vec4>());
                        cc.m_Camera->SetFOV(cam["FieldOfView"].as<float>());
                        cc.m_Camera->SetFOVAxis(cam["FieldOfViewAxis"].as<int>());
                        cc.m_Camera->SetAspectRatio(cam["AspectRatio"].as<float>());
                        cc.m_Camera->SetFixedAspectRatio(cam["FixedAspectRatio"].as<bool>());
                        cc.m_Camera->SetNearClip(cam["NearClip"].as<float>());
                        cc.m_Camera->SetFarClip(cam["FarClip"].as<float>());
                        cc.m_Camera->SetTransform(cam["Transform"].as<glm::mat4>());
                        cc.m_Camera->SetZoomLevel(cam["ZoomLevel"].as<float>());
                        cc.m_Camera->SetMoveSpeed(cam["MoveSpeed"].as<float>());
                        cc.m_Camera->SetRotateSpeed(cam["RotateSpeed"].as<float>());
                        VM_CORE_TRACE("Set Camera Settings");
                    }
                }
            }
            return true;
        }
        bool SceneSerializer::DeserializeRuntime(const std::string &filepath)
        {
            VM_CORE_ASSERT(false, "Runtime Scene Deserialization Not Implemented.");
            return false;
        }
    } // namespace ECS

} // namespace VersaMachina

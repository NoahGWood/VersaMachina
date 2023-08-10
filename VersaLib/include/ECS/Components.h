#pragma once
#include "Camera/Camera.h"
#include "Core/Base.h"
#include "Render/Texture.h"
#include "ECS/ScriptableEntity.h"
#include <glm/glm.hpp>
#include <string>

namespace VersaMachina
{
    namespace ECS
    {
        struct TagComponent
        {
            std::string Tag = "None";
            TagComponent() = default;
            TagComponent(const TagComponent&) = default;
            TagComponent(const std::string tag)
                : Tag(tag) {}
        };
        struct TransformComponent
        {
            glm::mat4 Transform;
            glm::vec3 Translation = {0.0f, 0.0f, 0.0f };
            glm::vec3 Rotation = {0.0f, 0.0f, 0.0f };
            glm::vec3 Scale = {1.0f, 1.0f, 1.0f };
            
            TransformComponent() = default;
            TransformComponent(const TransformComponent&) = default;
            TransformComponent(const glm::vec3& translation)
                : Translation(translation) {}

            glm::mat4& GetTransform()
            {
                glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), Rotation.x, {1,0,0})
                    * glm::rotate(glm::mat4(1.0f), Rotation.y, {0,1,0})
                    * glm::rotate(glm::mat4(1.0f), Rotation.z, {0,0,1});
                Transform = glm::translate(glm::mat4(1.0f), Translation) * rotation * glm::scale(glm::mat4(1.0f), Scale);
                return Transform;
            }
            
        };
        struct SpriteRendererComponent
        {
            glm::vec4 Color{1.0f, 1.0f, 1.0f, 1.0f};
            Ref<Render::Texture2D> Texture;
            SpriteRendererComponent() = default;
            SpriteRendererComponent(const SpriteRendererComponent&) = default;
            SpriteRendererComponent(const glm::vec4& color)
                : Color(color) {}
        };
        struct CameraComponent
        {
            Camera::Camera* m_Camera;
            bool Primary = true; // TODO: Move to scene controls
            
            CameraComponent()
                : m_Camera(new Camera::Camera()) { }
            CameraComponent(const CameraComponent&) = default;
            CameraComponent(Camera::Camera* camera)
                : m_Camera(camera) { }
            CameraComponent(Camera::Camera* camera, bool primary)
                : m_Camera(camera), Primary(primary) { }
 
        };
        struct NativeScriptComponent
        {
            ScriptableEntity* Instance = nullptr;

            ScriptableEntity*(*InstantiateScript)();
            void (*DestroyScript)(NativeScriptComponent*);

            template<typename T>
            void Bind()
            {
                InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
    			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
            }

        };
        struct ScriptComponent
        {

        };
    } // namespace ECS
    
} // namespace VersaMachina

#pragma once
#include "Camera/Camera.h"
#include "Core/Base.h"
#include "Render/Texture.h"

#include <glm/glm.hpp>
#include <string>

namespace VersaMachina
{
    namespace Scenes
    {
        struct TagComponent
        {
            std::string Tag;
            TagComponent() = default;
            TagComponent(const TagComponent&) = default;
            TagComponent(const std::string tag)
                : Tag(tag) {}
        };
        struct TransformComponent
        {
            glm::mat4 Transform;
            
            TransformComponent() = default;
            TransformComponent(const TransformComponent&) = default;
            TransformComponent(const glm::mat4& transform)
                : Transform(transform) {}

            operator glm::mat4&() { return Transform; }
            operator const glm::mat4&() const { return Transform; }
            
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
    } // namespace Scene
    
} // namespace VersaMachina

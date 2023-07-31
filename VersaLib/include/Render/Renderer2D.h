#pragma once
#include "Render/RenderCommand.h"
#include "Camera/Camera.h"

// temp
#include "Render/Texture.h"
#include "Render/Shader.h"

namespace VersaMachina
{
    namespace Render
    {
        class Renderer2D
        {
            public:
                static void Init();
                static void Shutdown();
                static void BeginScene(const Camera::Camera& camera);
                static void EndScene();

                // Primitives
                static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
                static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
                static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
                static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);
                static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color);

        };
    } // namespace Render
    
} // namespace VersaMachina

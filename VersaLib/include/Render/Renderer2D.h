#pragma once
#include "Render/RenderCommand.h"
#include "Camera/Camera.h"

// temp
#include "Render/Texture.h"
#include "Render/Shader.h"
#include <array>

namespace VersaMachina
{
    namespace Render
    {

        struct Statistics
        {
            uint32_t DrawCalls=0;
            uint32_t QuadCount = 0;
            uint32_t GetTotalVertexCount() { return QuadCount * 4; }
            uint32_t GetTotalIndexCount() { return QuadCount * 6; }
        };
    
        class Renderer2D
        {
            public:
                static void Init();
                static void Shutdown();
                static void BeginScene(const Camera::Camera& camera);
                static void EndScene();
                static void Flush();

                // Primitives
                static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) { DrawQuad({position.x, position.y, 0.0f}, size, nullptr, 1.0f, color); }
                static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) { DrawQuad(position, size, nullptr, 1.0f, color);}
                static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture) { DrawQuad({position.x, position.y, 0.0f}, size, texture, 1.0f, glm::vec4(1.0f)); }
                static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture) { DrawQuad(position, size, texture, 1.0f, glm::vec4(1.0f)); }
                static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color) { DrawQuad({position.x, position.y, 0.0f}, size, texture, 1.0f, color); }
                static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color) { DrawQuad(position, size, texture, 1.0f, color); }
                static void DrawQuad(const glm::vec3& position={0.0f,0.0f,0.0f}, const glm::vec2& size={1,1}, const Ref<Texture2D>& texture=nullptr, float tilingFactor=1.0f, const glm::vec4& color={1.0f,1.0f,1.0f,1.0f}) { DrawQuad(position, size, {0.0f,0.0f,0.0f}, {0.0f,0.0f,0.0f}, texture, tilingFactor, color); }
                static void DrawQuad(const glm::vec3& position={0.0f,0.0f,0.0f}, const glm::vec2& size={1,1}, const glm::vec3& rotation={0.0f,0.0f,0.0f}, const glm::vec3& translation={0.0f,0.0f,0.0f}, const Ref<Texture2D>& texture=nullptr, float tilingFactor=1.0f, const glm::vec4& color={1.0f,1.0f,1.0f,1.0f});

                static void ResetStats();
                static Statistics GetStats();

            private:
                static void FlushAndReset();
        };
    } // namespace Render
    
} // namespace VersaMachina

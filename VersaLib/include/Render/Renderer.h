#pragma once
#include "Render/RenderCommand.h"
#include "Camera/Camera.h"

// temp
#include "Render/Shader.h"
namespace VersaMachina
{
    namespace Render
    {
        class  Renderer
        {
            public:
                static void Init();

                static void OnWindowResize(uint32_t width, uint32_t height);

                static void BeginScene(Camera::Camera& camera);
                static void EndScene();

                static void Submit(
                    const Ref<Shader>& shader,
                    const Ref<VertexArray>& vertexArray,
                    const glm::mat4& transform = glm::mat4(1.0f));
                
                inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI();  }
            private:
                struct SceneData
                {
                    glm::mat4 ViewProjectionMatrix;
                };
                static Scope<SceneData> m_SceneData;
                static Camera::Camera& m_Camera;
        };
    } // namespace Render
    
} // namespace VersaMachina

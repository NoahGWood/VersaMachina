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
                static void BeginScene(Camera::Camera& camera);

                static void EndScene();

                static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);
                
                inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI();  }
            private:
                struct SceneData
                {
                    glm::mat4 ViewProjectionMatrix;
                };
                static SceneData* m_SceneData;
                static Camera::Camera& m_Camera;
        };
    } // namespace Render
    
} // namespace VersaMachina

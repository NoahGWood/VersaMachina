#include "pch.h"
#include "Render/Renderer.h"
#include "OpenGL/include/OpenGLShader.h"
namespace VersaMachina
{
    namespace Render
    {

        Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

        void Renderer::BeginScene(Camera::Camera& camera)
        {
            m_SceneData->ViewProjectionMatrix = camera.getViewProjectionMatrix();
        }
        void Renderer::EndScene()
        {
        }
        void Renderer::Submit(
            const Ref<Shader>& shader,
            const Ref<VertexArray>& vertexArray,
            const glm::mat4& transform
        )
        {
            shader->Bind();
            std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
            std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);
            vertexArray->Bind();
            RenderCommand::DrawIndexed(vertexArray);
        }
    } // namespace Render
    
} // namespace VersaMachina

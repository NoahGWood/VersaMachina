#include "pch.h"
#include "Render/Renderer.h"

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
        void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
        {
            shader->Bind();
            shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
            vertexArray->Bind();
            RenderCommand::DrawIndexed(vertexArray);
        }
    } // namespace Render
    
} // namespace VersaMachina

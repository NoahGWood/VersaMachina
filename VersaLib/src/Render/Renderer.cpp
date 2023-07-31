#include "pch.h"
#include "Render/Renderer.h"
#include "Render/Renderer2D.h"

#include "OpenGL/include/OpenGLShader.h"

namespace VersaMachina
{
    namespace Render
    {

        Scope<Renderer::SceneData> Renderer::m_SceneData = CreateScope<Renderer::SceneData>();

        void Renderer::Init()
        {
            RenderCommand::Init();
            Renderer2D::Init();
        }

        void Renderer::OnWindowResize(uint32_t width, uint32_t height)
        {
            RenderCommand::SetViewport(0,0, width, height);
        }

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
            shader->SetMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
            shader->SetMat4("u_Transform", transform);
            vertexArray->Bind();
            RenderCommand::DrawIndexed(vertexArray);
        }
    } // namespace Render
    
} // namespace VersaMachina

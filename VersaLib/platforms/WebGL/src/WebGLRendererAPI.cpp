#include "pch.h"
#include "WebGL/include/WebGLRendererAPI.h"

#include <glad/glad.h>

namespace VersaMachina
{
    namespace Render
    {
        void WebGLRendererAPI::SetClearColor(const glm::vec4& color)
        {
            glClearColor(color.r, color.g, color.b, color.a);
        }

        void WebGLRendererAPI::Clear()
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void WebGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
        {
            glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
        }
    } // namespace Render
    
} // namespace VersaMachina

#include "pch.h"
#include "Render/Renderer.h"
#include "Render/Shader.h"
#include "OpenGL/include/OpenGLShader.h"

namespace VersaMachina
{
    namespace Render
    {
        Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
        {
            switch(Renderer::GetAPI())
            {
                case RendererAPI::API::None :       VM_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported."); break;
                case RendererAPI::API::OpenGL :     return new OpenGLShader(vertexSrc, fragmentSrc);
            }
            VM_CORE_ASSERT(false, "Unknown RendererAPI!");
            return nullptr;
        }
    } // namespace Render
    
} // namespace VersaMachina

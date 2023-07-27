#include "pch.h"
#include "Render/VertexArray.h"
#include "Render/Renderer.h"

#include "OpenGL/include/OpenGLVertexArray.h"

namespace VersaMachina
{
    namespace Render
    {
        VertexArray* VertexArray::Create()
        {
           switch(Renderer::GetAPI())
            {
                case RendererAPI::API::None: VM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
                case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
            }
            VM_CORE_ASSERT(false);
            return nullptr;
        }
    } // namespace Render
    
} // namespace VersaMachina
#include "pch.h"
#include "Render/VertexBuffer.h"
#include "Render/Renderer.h"

#include "OpenGL/include/OpenGLBuffer.h"

namespace VersaMachina
{
    namespace Render
    {
        VertexBuffer* VertexBuffer::Create(uint32_t size, float* vertices)
        {
            switch(Renderer::GetAPI())
            {
                case RendererAPI::API::None:
                {
                    VM_CORE_ASSERT(false, "RenderAPI::None is not supported.");
                    return nullptr;
                }
                case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(size, vertices);
            }
            VM_CORE_ASSERT(false);
            return nullptr;
        }
    } // namespace Render
    
}
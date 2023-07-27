#include "pch.h"
#include "Render/IndexBuffer.h"
#include "Render/Renderer.h"

#include "OpenGL/include/OpenGLBuffer.h"

namespace VersaMachina
{
    namespace Render
    {
        IndexBuffer* IndexBuffer::Create(uint32_t size, uint32_t* indices)
        {
            switch(Renderer::GetAPI())
            {
                case RendererAPI::API::None:
                {
                    VM_CORE_ASSERT(false, "RenderAPI::None is not supported.");
                    return nullptr;
                }
                case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(size, indices);
            }
            VM_CORE_ASSERT(false);
            return nullptr;
        }
    } // namespace Render
    
} // namespace VersaMachina

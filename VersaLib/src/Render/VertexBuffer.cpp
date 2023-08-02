#include "pch.h"
#include "Render/VertexBuffer.h"
#include "Render/Renderer.h"

#include "OpenGL/include/OpenGLBuffer.h"

namespace VersaMachina
{
    namespace Render
    {

        Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
        {
            switch(Renderer::GetAPI())
            {
                case RendererAPI::API::None:
                {
                    VM_CORE_ASSERT(false, "RenderAPI::None is not supported.");
                    return nullptr;
                }
                case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(size);
            }
            VM_CORE_ASSERT(false, "Unknown RenderAPI!");
            return nullptr;
        }
        
        Ref<VertexBuffer> VertexBuffer::Create(uint32_t size, float* vertices)
        {
            switch(Renderer::GetAPI())
            {
                case RendererAPI::API::None:
                {
                    VM_CORE_ASSERT(false, "RenderAPI::None is not supported.");
                    return nullptr;
                }
                case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(size, vertices);
            }
            VM_CORE_ASSERT(false);
            return nullptr;
        }
    } // namespace Render
    
}
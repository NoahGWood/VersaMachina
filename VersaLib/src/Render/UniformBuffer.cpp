#include "pch.h"
#include "Render/UniformBuffer.h"

#include "Render/Renderer.h"
#include "OpenGL/include/OpenGLUniformBuffer.h"

namespace VersaMachina
{
    namespace Render
    {
        Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
        {
            switch(Renderer::GetAPI())
            {
			case RendererAPI::API::None:    VM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLUniformBuffer>(size, binding);
    		}
    		VM_CORE_ASSERT(false, "Unknown RendererAPI!");
    		return nullptr;
        }        
    } // namespace Render
    
} // namespace VersaMachina

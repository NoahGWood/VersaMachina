#include "pch.h"
#include "Render/Framebuffer.h"
#include "Render/Renderer.h"

#include "OpenGL/include/OpenGLFramebuffer.h"

namespace VersaMachina
{
    namespace Render
    {
        Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
        {
            switch(Renderer::GetAPI())
            {
    			case RendererAPI::API::None:    VM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
    			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLFramebuffer>(spec);
            }
            VM_CORE_ASSERT(false, "Unknown RendererAPI!");
    		return nullptr;
        }
    } // namespace Render
        
} // namespace VersaMachina

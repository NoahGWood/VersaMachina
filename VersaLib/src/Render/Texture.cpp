#include "pch.h"
#include "Render/Texture.h"
#include "Render/Renderer.h"

#include "OpenGL/include/OpenGLTexture.h"

namespace VersaMachina
{
    namespace Render
    {       
       
        Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
        {
            switch(Renderer::GetAPI())
            {
                case RendererAPI::API::None: VM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
                case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(width, height);
            }
            VM_CORE_ASSERT(false);
            return nullptr;
        }

        Ref<Texture2D> Texture2D::Create(const std::string& path)
        {
            switch(Renderer::GetAPI())
            {
                case RendererAPI::API::None: VM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
                case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(path);
            }
            VM_CORE_ASSERT(false);
            return nullptr;
        }
    } // namespace Render
    
} // namespace VersaMachina

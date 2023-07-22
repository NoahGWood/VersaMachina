#include "pch.h"
#include "Renderer/GraphicsContext.h"

#include "Renderer/Renderer.h"
#include "platforms/OpenGL/OpenGLContext.h"

namespace VersaMachina
{
    Scope<GraphicsContext> GraphicsContext::Create(void* window)
    {
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    VM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		VM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
    }
} // namespace VersaMachina

#include "pch.h"
#include "Render/RenderCommand.h"

#include "OpenGL/include/OpenGLRendererAPI.h"

namespace VersaMachina
{
    namespace Render
    {
        Scope<RendererAPI> RenderCommand::s_RendererAPI = CreateScope<OpenGLRendererAPI>();
    } // namespace Render
    
} // namespace VersaMachina

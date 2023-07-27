#include "pch.h"
#include "Render/RenderCommand.h"

#include "OpenGL/include/OpenGLRendererAPI.h"

namespace VersaMachina
{
    namespace Render
    {
        RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
    } // namespace Render
    
} // namespace VersaMachina

#pragma once

#include "Render/RenderContext.h"

class GLFWwindow;

namespace VersaMachina
{
    namespace Render
    {
        class OpenGLRenderContext : public RenderContext
        {
            public:
                OpenGLRenderContext(GLFWwindow* windowHandle);
                virtual void Init() override;
                virtual void SwapBuffers() override;
            private:
                GLFWwindow* m_WindowHandle;

        };
    } // namespace Render
    
} // namespace VersaMachina

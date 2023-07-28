#pragma once

#include "Render/RenderContext.h"

class GLFWwindow;

namespace VersaMachina
{
    namespace Render
    {
        class WebGLRenderContext : public RenderContext
        {
            public:
                WebGLRenderContext(GLFWwindow* windowHandle);
                virtual void Init() override;
                virtual void SwapBuffers() override;
            private:
                GLFWwindow* m_WindowHandle;

        };
    } // namespace Render
    
} // namespace VersaMachina

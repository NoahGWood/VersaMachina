#include "pch.h"
#include "OpenGL/include/OpenGLRenderContext.h"

#include <glad/glad.h>
#include "GLFW/glfw3.h"

namespace VersaMachina
{
    namespace Render
    {
        OpenGLRenderContext::OpenGLRenderContext(GLFWwindow* windowHandle)
            : m_WindowHandle(windowHandle)
        {
            VM_CORE_ASSERT(windowHandle, "Window handle is null!");
        }

        void OpenGLRenderContext::Init()
        {
            glfwMakeContextCurrent(m_WindowHandle);
            // Setup Glad
            int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
            VM_CORE_ASSERT(status, "Failed to initialize glad.");        
        }

        void OpenGLRenderContext::SwapBuffers()
        {
            glfwSwapBuffers(m_WindowHandle);

        }
    } // namespace Render
    
} // namespace VersaMachina

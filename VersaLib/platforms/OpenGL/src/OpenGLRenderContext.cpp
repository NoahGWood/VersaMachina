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
            char* vendor = (char*)glGetString(GL_VENDOR);
            char* renderer = (char*)glGetString(GL_RENDERER);
            char* version = (char*)glGetString(GL_VERSION);

            VM_CORE_INFO("OpenGL Info:");
            VM_CORE_INFO("  Vendor: {0}", vendor);
            VM_CORE_INFO("  Renderer: {0}", renderer);
            VM_CORE_INFO("  Version: {0}", (char*)glGetString(GL_VERSION));              
        }

        void OpenGLRenderContext::SwapBuffers()
        {
            glfwSwapBuffers(m_WindowHandle);

        }
    } // namespace Render
    
} // namespace VersaMachina

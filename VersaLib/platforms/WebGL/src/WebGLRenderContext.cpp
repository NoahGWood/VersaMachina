#include "pch.h"
#include "WebGL/include/WebGLRenderContext.h"

#include <glad/glad.h>
#include "GLFW/glfw3.h"

namespace VersaMachina
{
    namespace Render
    {
        WebGLRenderContext::WebGLRenderContext(GLFWwindow* windowHandle)
            : m_WindowHandle(windowHandle)
        {
            VM_CORE_ASSERT(windowHandle, "Window handle is null!");
        }

        void WebGLRenderContext::Init()
        {
            glfwMakeContextCurrent(m_WindowHandle);
            // Setup Glad
            int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
            VM_CORE_ASSERT(status, "Failed to initialize glad.");
            char* vendor = (char*)glGetString(GL_VENDOR);
            char* renderer = (char*)glGetString(GL_RENDERER);
            char* version = (char*)glGetString(GL_VERSION);

            VM_CORE_INFO("WebGL Info:");
            VM_CORE_INFO("  Vendor: {0}", vendor);
            VM_CORE_INFO("  Renderer: {0}", renderer);
            VM_CORE_INFO("  Version: {0}", (char*)glGetString(GL_VERSION));              
        }

        void WebGLRenderContext::SwapBuffers()
        {
            glfwSwapBuffers(m_WindowHandle);

        }
    } // namespace Render
    
} // namespace VersaMachina

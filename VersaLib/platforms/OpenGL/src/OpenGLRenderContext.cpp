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

            VM_PROFILE_FUNCTION();
            
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

            #ifdef VM_ENABLE_ASSERTS
                int versionMajor;
                int versionMinor;
        		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
        		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

        		VM_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "VersaMachina requires at least OpenGL version 4.5!");
            #endif     
        }

        void OpenGLRenderContext::SwapBuffers()
        {
            VM_PROFILE_FUNCTION();

            glfwSwapBuffers(m_WindowHandle);

        }
    } // namespace Render
    
} // namespace VersaMachina

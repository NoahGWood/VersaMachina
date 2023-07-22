#include "pch.h"
#include "OpenGL/include/OpenGLWindow.h"

#include <GLFW/glfw3.h>

namespace VersaMachina
{
    static bool s_GLFWInitialized = false;

    Window* Window::Create(const WindowProps& props)
    {
        return new OpenGLWindow(props);
    }

    OpenGLWindow::OpenGLWindow(const WindowProps& props)
    {
        Init(props);
    }

    OpenGLWindow::~OpenGLWindow()
    {
        Shutdown();
    }

    void OpenGLWindow::Init(const WindowProps& props)
    {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        VM_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

        if(!s_GLFWInitialized)
        {
            int success = glfwInit();
            VM_CORE_ASSERT(success, "Could not initialize GLFW!");

            s_GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);
        glfwSwapBuffers(m_Window);
    }

    void OpenGLWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

    void OpenGLWindow::OnUpdate()
    {
        if(!glfwWindowShouldClose(m_Window))
        {
            glfwSwapBuffers(m_Window);
            glfwPollEvents();
        }
    }

    void OpenGLWindow::SetVSync(bool enabled)
    {
        if(enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
    }


} // namespace VersaMachina

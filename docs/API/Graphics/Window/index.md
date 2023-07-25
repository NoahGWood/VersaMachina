# Windows

Windows in VersaMachina are implemented as an abstract class which is then subclassed for each target platform.

## Window Properties

- Title
- Width
- Height

## Window Functions

- OnUpdate()
    - The main update loop.
- GetWidth()
    - Returns the width of the window
- GetHeight()
    - Returns the height of the window
- SetEventCallback(const EventCallbackFn& callback)
    - Takes in an Event callback function reference allowing you to hook your window into the [Events](../../Events/index.md) system.
- SetVSync(bool enabled)
    - Used to enable/disable VSync
- GetNativeWindow()
    - Returns a pointer to the native window (e.g. OpenGL, Vulkan)
- Create(const WindowProps& props = WindowProps())
    - Used to create a new window instance.

## Examples

### OpenGLWindow.h

```
#pragma once
#include "Core/Window.h"
#include "OpenGL/include/OpenGLRenderContext.h"
 
// Forward declare GLFWwindow to avoid including glfw3.h
struct GLFWwindow;
//#include <glad/glad.h>

namespace VersaMachina
{
    class OpenGLWindow : public Window
    {
        public:
            OpenGLWindow(const WindowProps& props);
            virtual ~OpenGLWindow();

            void OnUpdate() override;

            inline unsigned int GetWidth() const override { return m_Data.Width; }
            inline unsigned int GetHeight() const override { return m_Data.Height; }

            inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
            void SetVSync(bool enabled);
            bool IsVSync() const;
            
            inline virtual void* GetNativeWindow() const { return m_Window; }

        private:
            virtual void Init(const WindowProps& props);
            virtual void Shutdown();

        private:
            GLFWwindow* m_Window;
            Render::OpenGLRenderContext* m_Context;

            struct WindowData
            {
                std::string Title;
                unsigned int Width, Height;
                EventCallbackFn EventCallback;
                /* data */
            };
            WindowData m_Data;
            
    };
} // namespace VersaMachina
```

### OpenGLWindow.cpp
```
#include "pch.h"
#include "OpenGL/include/OpenGLWindow.h"
#include "OpenGL/include/OpenGLRenderContext.h"

#include "Events/WindowEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include <GLFW/glfw3.h>

namespace VersaMachina
{

    static bool s_GLFWInitialized = false;

    static void GLFWErrorCallback(int error, const char* description)
    {
        VM_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }

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
            // Set error callback
            glfwSetErrorCallback(GLFWErrorCallback);
            s_GLFWInitialized = true;
        }

        // Setup window
        m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);

        m_Context = new Render::OpenGLRenderContext(m_Window);
        m_Context->Init();
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        // Set GLFW callbacks
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowResizedEvent event(width, height);
            data.Width = width;
            data.Height = height;
            data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch(action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, true);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y )
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseMovedEvent event((float)x, (float)y);
            data.EventCallback(event);
        });
    }

    void OpenGLWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

    void OpenGLWindow::OnUpdate()
    {
        
        if(!glfwWindowShouldClose(m_Window))
        {
            glfwPollEvents();
            m_Context->SwapBuffers();
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

```

[DearImGUI](https://github.com/ocornut/imgui) is used in the backend to render windows.


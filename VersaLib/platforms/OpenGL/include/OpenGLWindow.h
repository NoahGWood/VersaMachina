#pragma once
#include "Core/Window.h"

//#include "OpenGL/include/OpenGLWindow.h"
//#include "Events/WindowEvent.h"
//#include "Events/MouseEvent.h"
//#include "Events/KeyEvent.h"
//#define _GLFW_X11 1
//#include <GLFW/glfw3.h>

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

        private:
            virtual void Init(const WindowProps& props);
            virtual void Shutdown();

        private:
            GLFWwindow* m_Window;

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

#pragma once
#include "Core/Window.h"

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

//            inline void InitBackend() const override {
//                // Setup Platform/Renderer backends
//                ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
//            }

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

#pragma once
#include "Core/Window.h"
#include "WebGL/include/WebGLRenderContext.h"
 
// Forward declare GLFWwindow to avoid including glfw3.h
struct GLFWwindow;
//#include <glad/glad.h>

namespace VersaMachina
{
    class WebGLWindow : public Window
    {
        public:
            WebGLWindow(const WindowProps& props);
            virtual ~WebGLWindow();

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
            Render::WebGLRenderContext* m_Context;

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

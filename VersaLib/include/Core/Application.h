#pragma once

#include "Core/Log.h"
#include "Core/Window.h"
#include "Core/LayerStack.h"
#include "Events/Event.h"
#include "Events/WindowEvent.h"

namespace VersaMachina
{
    class Application
    {
        public:
            Application();
            virtual ~Application();

            void Run();

            void OnEvent(Event& e);

            // Layers

    		void PushLayer(Layer* layer);
    		void PushOverlay(Layer* layer);
            
            inline static Application& Get() { return *s_Instance; }
            inline Window& GetWindow() { return *m_Window; }
        private:
            // Layers
            LayerStack m_LayerStack;
            // Windows
            bool OnWindowClose(WindowCloseEvent& e);
            std::unique_ptr<Window> m_Window;
            // Stats
            bool m_Running = true;

            static Application* s_Instance;
    };
    
    // Defined in client
    Application* CreateApplication();

} // namespace VersaMachina

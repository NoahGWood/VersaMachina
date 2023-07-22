#pragma once

#include "Core/Log.h"
#include "Events/Event.h"
#include "Events/WindowEvent.h"

#include "Core/Window.h"

#include "Core/LayerStack.h"

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
        private:
            LayerStack m_LayerStack;
            bool OnWindowClose(WindowCloseEvent& e);

            std::unique_ptr<Window> m_Window;
            bool m_Running = true;
    };
    
    // Defined in client
    Application* CreateApplication();

} // namespace VersaMachina

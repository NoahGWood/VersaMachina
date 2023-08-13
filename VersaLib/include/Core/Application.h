#pragma once
// Core
#include "Core/Log.h"
#include "Core/Window.h"
#include "Core/LayerStack.h"
#include "Core/Input.h"
#include "Core/Timestep.h"

// Events
#include "Events/Event.h"
#include "Events/WindowEvent.h"
// Layers
#include "UI/ImGUILayer.h"

namespace VersaMachina
{
    struct ApplicationCommandLineArgs
    {
        int Count = 0;
        char** Args = nullptr;
        const char* operator[](int index) const
        {
            VM_CORE_ASSERT(index < Count);
            return Args[index];
        }
    };

    class Application
    {
        public:
            Application(const std::string& name = "Versa App", ApplicationCommandLineArgs args = ApplicationCommandLineArgs());
            virtual ~Application();

            void Run();

            void OnEvent(Event& e);

            // CLI Args
            ApplicationCommandLineArgs GetCommandLineArgs() const { return m_CommandLineArgs; }

            // Layers

    		void PushLayer(Layer* layer);
    		void PushOverlay(Layer* layer);
            
            inline static Application& Get() { return *s_Instance; }
            inline Window& GetWindow() { return *m_Window; }

            UI::ImGUILayer* GetImGuiLayer() { return m_ImGUILayer; }

        private:
            bool OnWindowClose(WindowCloseEvent& e);
            bool OnWindowResize(WindowResizedEvent& e);
            
        private:
            ApplicationCommandLineArgs m_CommandLineArgs;
            static Application* s_Instance;
            float m_LastFrameTime = 0.0f;
            // Layers
            LayerStack m_LayerStack;
            UI::ImGUILayer* m_ImGUILayer; 
            // Windows
            Scope<Window> m_Window;
            // Stats
            bool m_Running = true;
            bool m_Minimized = false;

    };
    
    // Defined in client
    Application* CreateApplication(ApplicationCommandLineArgs args);

} // namespace VersaMachina

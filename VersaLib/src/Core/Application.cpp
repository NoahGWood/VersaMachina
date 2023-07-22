#include "pch.h"
#include "Core/Application.h"

//#include <GLFW/glfw3.h>

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace VersaMachina
{
    Application::Application()
    {
        VM_PROFILE_FUNCTION();
        m_Window = std::unique_ptr<Window>(Window::Create());
//        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
    }
    Application::~Application()
    {
        VM_PROFILE_FUNCTION();
    }

    // Layers
    void Application::PushLayer(Layer* layer)
    {
        VM_PROFILE_FUNCTION();

        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay)
    {
        VM_PROFILE_FUNCTION();

        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();                
    }

    void Application::Run() {
        VM_PROFILE_FUNCTION();
        while(m_Running)
        {
//            glClearColor(1,0,1,1);
//            glClear(GL_COLOR_BUFFER_BIT);
            m_Window->OnUpdate();
        }
    }


    void Application::OnEvent(Event& e)
    {
        VM_PROFILE_FUNCTION();
//        VM_CORE_TRACE("{0}", e);
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }

} // namespace VersaMachina

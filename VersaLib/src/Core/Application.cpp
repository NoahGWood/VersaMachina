#include "pch.h"
#include "Core/Application.h"
#include "Render/Renderer.h"
#include "Render/BufferLayout.h"
#include "Render/RendererAPI.h"

#include "Camera/Camera.h"

#include <GLFW/glfw3.h>

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace VersaMachina
{

    Application *Application::s_Instance = nullptr;

    Application::Application(const std::string& name, ApplicationCommandLineArgs args)
        : m_CommandLineArgs(args)
    {
        VM_CORE_ASSERT(!s_Instance, "Application already exists.")
        s_Instance = this;

        VM_PROFILE_FUNCTION();
        m_Window = Scope<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

        Render::Renderer::Init();

        m_ImGUILayer = new UI::ImGUILayer();
        PushOverlay(m_ImGUILayer);

    }
    Application::~Application()
    {
        VM_PROFILE_FUNCTION();
    }

    // Layers
    void Application::PushLayer(Layer *layer)
    {
        VM_PROFILE_FUNCTION();

        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *overlay)
    {
        VM_PROFILE_FUNCTION();

        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    void Application::Run()
    {
        VM_PROFILE_FUNCTION();

        while (m_Running)
        {
            VM_PROFILE_SCOPE("Application::Run");
    
            float time = (float)glfwGetTime()*1000.0f; // Platform::GetTime();
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;
            if(!m_Minimized)
            {
                VM_PROFILE_SCOPE("LayerStack Updates - Application::Run");
                for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
                {
                    (*it)->OnUpdate(timestep);
                }
            }
            {
                VM_PROFILE_SCOPE("ImGUI Layer Updates - Application:Run");
                m_ImGUILayer->Begin();
                for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
                {
                    (*it)->OnImGuiRender();
                }
                m_ImGUILayer->End();
            }
            m_Window->OnUpdate();
            //            auto[x,y] = Input::Input::GetMousePos();
            //            VM_CORE_CRITICAL("{0}, {1}", x,y);
        }
    }

    void Application::OnEvent(Event &e)
    {
        VM_PROFILE_FUNCTION();

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizedEvent>(BIND_EVENT_FN(OnWindowResize));
        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
        {
            if (e.m_Handled)
            {
                break;
            }
            (*it)->OnEvent(e);
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent &e)
    {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizedEvent &e)
    {
        VM_PROFILE_FUNCTION();
        
        if(e.GetWidth() ==0 | e.GetHeight() == 0)
        {
            m_Minimized = true;
            return false;
        }
        m_Minimized = false;
        Render::Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
        return true;
    }

} // namespace VersaMachina

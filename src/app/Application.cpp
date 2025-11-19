#include <VM.h>
#include <ecs/Project.h>
namespace VM
{
    bool Application::Init(){
        CORE_TRACE("Initializing Application...");
        if(s_Instance){
            CORE_ERROR("Application already exists!");
            return false;
        }
        s_Instance = this;
        CORE_TRACE("Instantiating App Context");
        m_AppContext = AppContext::Create();
        bool win = m_AppContext->window().Init(m_AppContext);        
        if(!win) {
            CORE_FATAL("Failed to create window.");
        }
        CORE_TRACE("Window created.");
        
        CORE_TRACE("Registering menus.");
        m_AppContext->window().AddMenu<FileMenu>(m_AppContext);
        m_AppContext->window().AddMenu<EditMenu>(m_AppContext);
        m_AppContext->window().AddMenu<ToolsMenu>(m_AppContext);
        m_AppContext->window().AddMenu<ViewMenu>(m_AppContext);
        m_AppContext->window().AddMenu<HelpMenu>(m_AppContext);
        
        CORE_TRACE("Registering panels.");
        m_AppContext->window().AddPanel<MainPanel>(m_AppContext);
        m_AppContext->window().AddPanel<ConsolePanel>(m_AppContext);
        m_AppContext->window().AddPanel<ExporterPanel>(m_AppContext);
        m_AppContext->window().AddPanel<HardwarePanel>(m_AppContext);
        m_AppContext->window().AddPanel<InspectorPanel>(m_AppContext);
        m_AppContext->window().AddPanel<ProjectPanel>(m_AppContext);
        m_AppContext->window().AddPanel<ToolboxPanel>(m_AppContext);
        m_AppContext->window().AddPanel<StylePanel>(m_AppContext);

        CORE_TRACE("App::Init Complete.");
        return true;
    }

    bool Application::Tick(){
        auto now = std::chrono::steady_clock::now();
        m_DeltaTime = std::chrono::duration<double>(now - m_LastFrame).count();
        m_LastFrame = now;
        AppTickData data{
            .deltaTime = m_DeltaTime,
            .frame = ++m_Frame
        };
        Event tick{
            .category = EventCategory::App,
            .type = EventType::Tick,
            .data = data
        };
        m_AppContext->eventRouter().Emit(tick);
        m_AppContext->eventRouter().DrainQueuedEvents();
        return m_Running;        
    }

    bool Application::Shutdown(){
        if(m_ShutdownCalled) return false;
        m_ShutdownCalled = true;
        CORE_INFO("Shutting application down...");
        m_Running = false;
        CORE_INFO("Closing Window...");
        m_AppContext->window().Shutdown();
        return true;
    }

    void Application::Save(){

    }

    void Application::Load(){

    }

    void Application::New(){

    }
} // namespace VM

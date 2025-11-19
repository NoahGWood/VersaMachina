#pragma once
#include <common/Base.h>
#include <cmd/CommandManager.h>
#include <ecs/Project.h>
#include <common/StyleSheet.h>
// #include <window/Window.h>
// #include <event/EventRouter.h>
namespace VM
{
    // Forward declarations
    class EventRouter;
    // class Project;
    class Window;
    class BlockSpecRegistry;

    class AppContext : public std::enable_shared_from_this<AppContext>
    {
        public:
            static std::shared_ptr<AppContext> Create(){
                auto ctx = std::shared_ptr<AppContext>(new AppContext());
                CORE_TRACE("Instantiating Event Router...");
                ctx->m_EventRouter = std::make_unique<EventRouter>();
                CORE_TRACE("Instantiating ECS...");
                ctx->m_Project = std::make_unique<Project>();
                CORE_TRACE("Instantiating Window...");
                ctx->m_Window = std::make_unique<Window>();
                CORE_TRACE("Instantiating Command Manager...");
                ctx->m_CommandManager = std::make_unique<CommandManager>();
                return ctx;
            }


            EventRouter& eventRouter() { return *m_EventRouter; }
            Project& project() { return *m_Project; }
            Window& window() { return *m_Window; }
            CommandManager& cmdManager() { return *m_CommandManager; }
            BlockSpecRegistry& blockRegistry() { return *m_BlockRegistry; }


            AppContext(const AppContext&) = delete;
            AppContext& operator=(const AppContext&) = delete;

        private:
            AppContext() = default; // Force Create()
            std::unique_ptr<EventRouter> m_EventRouter;
            std::unique_ptr<Project> m_Project;
            std::unique_ptr<Window> m_Window;
            std::unique_ptr<CommandManager> m_CommandManager;
            std::unique_ptr<StyleSheet> m_StyleSheet;
            std::unique_ptr<BlockSpecRegistry> m_BlockRegistry;
    };
} // namespace VM

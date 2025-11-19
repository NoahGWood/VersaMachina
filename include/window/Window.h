#pragma once
#include <common/Base.h>
#include <event/EventRouter.h>
#include <SDL2/SDL.h>
#include <ui/IPanel.h>
#include <ui/IMenu.h>
namespace VM
{
    class Window{
        public:
            // ~Window() { Shutdown(); }
            bool Init(std::shared_ptr<AppContext> context);
            bool PollEvents();
            bool Tick(double dt);
            bool BeginFrame();
            bool EndFrame();
            bool Render();
            bool Shutdown();
            template<typename T, typename... Args>
            bool AddMenu(Args&&... args){
                m_Menus.push_back(std::make_unique<T>(std::forward<Args>(args)...));
                return true;
            }
            template<typename T, typename... Args>
            bool AddPanel(Args&&... args){
                m_Panels.push_back(std::make_unique<T>(std::forward<Args>(args)...));
                return true;
            }

            bool OpenPanel(const std::string& panelName){
                for(auto& p : m_Panels){
                    if(p->Name() == panelName){
                        p->Open();
                        return false;
                    }
                }
                CORE_ERROR("Panel " + panelName + "not found!");
                return false;
            }

            bool ClosePanel(const std::string& panelName){
                for(auto& p : m_Panels){
                    if(p->Name() == panelName){
                        p->Close();
                        return true;
                    }
                }
                CORE_ERROR("Panel " + panelName + "not found!");
                return false;
            }

        private:
            SDL_Window* m_Window;
            SDL_GLContext m_Context;
            std::shared_ptr<AppContext> m_AppContext;
            std::shared_ptr<EventRouter> m_EventRouter;
            std::vector<std::unique_ptr<IPanel>> m_Panels;
            std::vector<std::unique_ptr<IMenu>> m_Menus;
            int m_Width, m_Height;

    };    
} // namespace VM

#pragma once
#include <imgui.h>
#include <common/Base.h>
#include <ui/IMenu.h>
#include <event/EventRouter.h>

namespace VM
{
    class EditMenu : public IMenu
    {
        public:
            EditMenu(std::shared_ptr<AppContext> context)
                : IMenu(std::move(context)) { m_Name = "Edit"; }
            ~EditMenu(){ }
            void Open() { m_IsOpen = true; }
            void Tick() override {}
            void Render() override {
                if(ImGui::BeginMenu(m_Name.c_str())){
                    if(ImGui::MenuItem("Style")){
                        m_AppContext->window().OpenPanel("Style");
                    }
                    ImGui::EndMenu();
                }
            }
    };
} // namespace VM

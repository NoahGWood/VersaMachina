#pragma once
#include <imgui.h>
#include <common/Base.h>
#include <ui/IMenu.h>
#include <event/EventRouter.h>

namespace VM
{
    class ToolsMenu : public IMenu
    {
        public:
            ToolsMenu(std::shared_ptr<AppContext> context)
                : IMenu(std::move(context)) { m_Name = "Tools"; }
            ~ToolsMenu(){ }
            void Open() { m_IsOpen = true; }
            void Tick() override {}
            void Render() override {
                if(ImGui::BeginMenu(m_Name.c_str())){
                    ImGui::EndMenu();
                }
            }
    };
} // namespace VM

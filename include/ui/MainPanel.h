#pragma once
#include <imgui.h>
#include <common/Base.h>
#include <ui/IPanel.h>
#include <event/EventRouter.h>

namespace VM
{
    class MainPanel : public IPanel
    {
        public:
            MainPanel(std::shared_ptr<AppContext> context)
                : IPanel(std::move(context)) { m_Name = "Versa Machina"; }
            ~MainPanel(){
            }
            void Open() { m_IsOpen = true; }
            void Tick() override {}
            void Render() override;
    };
} // namespace VM

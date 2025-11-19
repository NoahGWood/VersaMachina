#pragma once
#include <imgui.h>
#include <common/Base.h>
#include <ui/IPanel.h>
#include <app/AppContext.h>

namespace VM
{
    class ToolboxPanel : public IPanel
    {
        public:
            ToolboxPanel(std::shared_ptr<AppContext> context)
                : IPanel(std::move(context)) { m_Name = "Toolbox"; }
            ~ToolboxPanel(){}
            void Open() { m_IsOpen = true; }
            void Tick() override {}
            void Render() override;
    };
} // namespace VM

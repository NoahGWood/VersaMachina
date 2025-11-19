#pragma once
#include <imgui.h>
#include <common/Base.h>
#include <ui/IPanel.h>
#include <app/AppContext.h>

namespace VM
{
    class InspectorPanel : public IPanel
    {
        public:
            InspectorPanel(std::shared_ptr<AppContext> context)
                : IPanel(std::move(context)) { m_Name = "Inspector"; }
            ~InspectorPanel(){
            }
            void Open() { m_IsOpen = true; }
            void Tick() override {}
            void Render() override;
    };
} // namespace VM

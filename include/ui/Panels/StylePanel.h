#pragma once
#include <imgui.h>
#include <common/Base.h>
#include <ui/IPanel.h>
#include <app/AppContext.h>

namespace VM
{
    class StylePanel : public IPanel
    {
        public:
            StylePanel(std::shared_ptr<AppContext> context)
                : IPanel(std::move(context)) { m_Name = "Style"; m_IsOpen=false; }
            ~StylePanel(){
            }
            void Open() { m_IsOpen = true; }
            void Tick() override {}
            void Render() override;
    };
} // namespace VM

#pragma once
#include <imgui.h>
#include <common/Base.h>
#include <ui/IPanel.h>
#include <app/AppContext.h>

namespace VM
{
    class HardwarePanel : public IPanel
    {
        public:
            HardwarePanel(std::shared_ptr<AppContext> context);
            ~HardwarePanel(){
            }
            void Open() { m_IsOpen = true; }
            void Tick() override {}
            void Render() override;    
    };
} // namespace VM

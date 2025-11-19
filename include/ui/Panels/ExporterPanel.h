#pragma once
#include <imgui.h>
#include <common/Base.h>
#include <ui/IPanel.h>
#include <app/AppContext.h>

namespace VM
{
    class ExporterPanel : public IPanel
    {
        public:
            ExporterPanel(std::shared_ptr<AppContext> context)
                : IPanel(std::move(context)) { m_Name = "Exporter"; }
            ~ExporterPanel(){
            }
            void Open() { m_IsOpen = true; }
            void Tick() override {}
            void Render() override;
    };
} // namespace VM

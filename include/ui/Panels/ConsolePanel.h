#pragma once
#include <imgui.h>
#include <common/Base.h>
#include <ui/IPanel.h>
#include <app/AppContext.h>

namespace VM
{
    class ConsolePanel : public IPanel
    {
        public:
            ConsolePanel(std::shared_ptr<AppContext> context)
                : IPanel(std::move(context)) {
                    m_Name = "Console";
                }
            ~ConsolePanel(){
            }
            void Open() { m_IsOpen = true; }
            void Tick() override {}
            void Render() override;

        private:
    };
} // namespace VM

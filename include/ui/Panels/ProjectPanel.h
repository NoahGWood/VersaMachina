#pragma once
#include <imgui.h>
#include <common/Base.h>
#include <ui/IPanel.h>
#include <app/AppContext.h>

namespace VM
{
    class ProjectPanel : public IPanel
    {
        public:
            ProjectPanel(std::shared_ptr<AppContext> context)
                : IPanel(std::move(context)) { m_Name = "Project"; }
            ~ProjectPanel(){
            }
            void Open() { m_IsOpen = true; }
            void Tick() override {}
            void Render() override;
            void RenderEntityNode(entt::entity e);
    };
} // namespace VM
